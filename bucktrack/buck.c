#include <unistd.h>     // write, read, close
#include <stdlib.h>     // malloc, free
#include <fcntl.h>      // open
#include <stdio.h>      // NULL, size_t
#include <string.h>     // strlen

// マップ情報をまとめる構造体
typedef struct s_map {
    char **map;       // マップ本体(行の配列)
    int height;       // 行数
    int width;        // 列数
    int totalC;       // マップに存在する'C'の総数
    int start_x;      // 'P'のx座標
    int start_y;      // 'P'のy座標
} t_map;

/*
 * get_next_line もしくは簡易的な行読み取り関数を用意する。
 * while文とif文のみで実装する場合は標準ライブラリのgetline等を使わず、
 * 自作の行読み取りロジックを入れることも可能ですが、
 * ここでは可読性のために簡易版を示します。
 */
static char *ft_readline(int fd)
{
    char buf[2];
    char *line;
    int  ret;
    int  len;

    line = NULL;
    len = 0;
    // 1文字ずつ読み取り
    while (1)
    {
        ret = read(fd, buf, 1);
        if (ret <= 0)
        {
            // ファイル終端またはエラー
            if (line == NULL)
                return NULL; 
            break;
        }
        if (buf[0] == '\n')
            break;
        buf[1] = '\0';

        // 既存のlineに1文字追加するためreallocのような処理
        // (while + ifのみで表現)
        {
            char *new_line;
            int  i;
            new_line = (char *)malloc(len + 2);
            if (!new_line)
            {
                free(line);
                return NULL;
            }
            i = 0;
            while (i < len)
            {
                new_line[i] = line[i];
                i++;
            }
            new_line[i] = buf[0];
            new_line[i + 1] = '\0';
            free(line);
            line = new_line;
            len++;
        }
    }
    return line;
}

// whileとifのみでstrlen相当を作る
static int ft_strlen(const char *s)
{
    int len;

    len = 0;
    while (s[len] != '\0')
    {
        len++;
    }
    return len;
}

// マップが長方形、周囲が'1'のみ、'P'が一つ、少なくとも'C'と'E'が一つ以上あるか確認
static int check_basic_errors(t_map *m)
{
    int y;
    int x;
    int countP;
    int countE;

    // 長方形かどうか: 全行の長さがm->widthと一致するか
    y = 0;
    while (y < m->height)
    {
        if (ft_strlen(m->map[y]) != m->width)
            return 0; // エラー
        y++;
    }

    // 周囲が'1'かどうか
    // 上下
    x = 0;
    while (x < m->width)
    {
        if (m->map[0][x] != '1' || m->map[m->height - 1][x] != '1')
            return 0;
        x++;
    }
    // 左右
    y = 0;
    while (y < m->height)
    {
        if (m->map[y][0] != '1' || m->map[y][m->width - 1] != '1')
            return 0;
        y++;
    }

    // 'P'が一つだけ、最低一つの'C'と'E'
    m->totalC = 0;
    countP = 0;
    countE = 0;
    y = 0;
    while (y < m->height)
    {
        x = 0;
        while (x < m->width)
        {
            if (m->map[y][x] == 'P')
                countP++;
            else if (m->map[y][x] == 'C')
                m->totalC++;
            else if (m->map[y][x] == 'E')
                countE++;
            else if (m->map[y][x] != '0' && m->map[y][x] != '1')
                return 0; // 無効な文字

            x++;
        }
        y++;
    }
    if (countP != 1 || m->totalC < 1 || countE < 1)
        return 0;

    // 'P'の座標も確認（後でバックトラックするときに使うため）
    // ここでは最初に見つけたPを格納
    y = 0;
    while (y < m->height)
    {
        x = 0;
        while (x < m->width)
        {
            if (m->map[y][x] == 'P')
            {
                m->start_x = x;
                m->start_y = y;
            }
            x++;
        }
        y++;
    }
    return 1; // OK
}

// 盤面範囲内かつ壁でないかチェック
static int is_valid(t_map *m, int x, int y, int **visited)
{
    if (x >= 0 && x < m->width && y >= 0 && y < m->height)
    {
        if (m->map[y][x] != '1' && visited[y][x] == 0)
            return 1;
    }
    return 0;
}

// バックトラックして、Pから全Cを拾ったうえでEに到達できるか調べる
static int backtrack(t_map *m, int x, int y, int *collected, int **visited)
{
    // 今いる場所がCならcollectedを増やす
    if (m->map[y][x] == 'C')
    {
        (*collected)++;
    }
    // Eに到達、かつCを全部拾えていればOK
    if (m->map[y][x] == 'E' && (*collected) == m->totalC)
        return 1;

    // 訪問済みにする
    visited[y][x] = 1;

    // 分岐する4方向
    // while文で4方向を回す（0:下,1:右,2:上,3:左など）
    int dirs[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
    int i = 0;
    while (i < 4)
    {
        int nx = x + dirs[i][0];
        int ny = y + dirs[i][1];

        if (is_valid(m,nx,ny,visited))
        {
            int res = backtrack(m,nx,ny,collected,visited);
            if (res == 1)
                return 1; // 到達可能

            // 戻ってきたらCの回収数を元に戻す
            // ただし移動先が'C'だった場合のみ減らす
            if (m->map[ny][nx] == 'C')
                (*collected)--;
        }
        i++;
    }

    // バックトラックで戻るときに訪問を解除
    visited[y][x] = 0;
    return 0;
}

int main(void)
{
    int fd;
    fd = open("date", O_RDONLY);
    if (fd < 0)
    {
        write(1, "Error\n", 6);
        return 1;
    }

    // マップ読み込み(1回目でheightとwidth計測)
    t_map m;
    m.height = 0;
    m.width  = 0;
    m.totalC = 0;
    m.start_x = 0;
    m.start_y = 0;

    char *line;
    while ((line = ft_readline(fd)) != NULL)
    {
        if (m.height == 0)
            m.width = ft_strlen(line);
        m.height++;
        free(line);
    }

    // メモリ確保
    m.map = (char **)malloc(sizeof(char *) * m.height);
    if (!m.map)
    {
        write(1, "Error\n", 6);
        close(fd);
        return 1;
    }

    // ファイル読み込み位置を先頭に戻す
    lseek(fd, 0, SEEK_SET);

    // 2回目でmap本体を格納
    int row = 0;
    while (1)
    {
        line = ft_readline(fd);
        if (!line)
            break;
        m.map[row] = line; 
        row++;
    }
    close(fd);

    // 基本エラーチェック
    if (check_basic_errors(&m) == 0)
    {
        write(1, "Error\n", 6);
        // 後始末
        int i2 = 0;
        while (i2 < m.height)
        {
            free(m.map[i2]);
            i2++;
        }
        free(m.map);
        return 1;
    }

    // バックトラック
    // visited配列(int型)を作成(0で初期化)
    int **visited;
    visited = (int **)malloc(sizeof(int*) * m.height);
    if (!visited)
    {
        write(1, "Error\n", 6);
        // 後始末
        int i2 = 0;
        while (i2 < m.height)
        {
            free(m.map[i2]);
            i2++;
        }
        free(m.map);
        return 1;
    }
    int yy = 0;
    while (yy < m.height)
    {
        visited[yy] = (int *)malloc(sizeof(int) * m.width);
        if (!visited[yy])
        {
            write(1, "Error\n", 6);
            // 後始末 (一部解放)
            int j2 = 0;
            while (j2 < yy)
            {
                free(visited[j2]);
                j2++;
            }
            free(visited);
            // map解放
            int j3 = 0;
            while (j3 < m.height)
            {
                free(m.map[j3]);
                j3++;
            }
            free(m.map);
            return 1;
        }
        // 0で初期化
        int xx = 0;
        while (xx < m.width)
        {
            visited[yy][xx] = 0;
            xx++;
        }
        yy++;
    }

    int collected = 0;
    int reachable = backtrack(&m, m.start_x, m.start_y, &collected, visited);

    if (reachable == 0)
    {
        write(1, "Error\n", 6);
    }

    // 後始末
    yy = 0;
    while (yy < m.height)
    {
        free(visited[yy]);
        yy++;
    }
    free(visited);

    // map本体
    yy = 0;
    while (yy < m.height)
    {
        free(m.map[yy]);
        yy++;
    }
    free(m.map);

    return 0;
}
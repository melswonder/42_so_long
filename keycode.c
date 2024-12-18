#include <stdio.h>
#include <X11/Xlib.h>
// #include "util.h"

int main(int argc,char **argv)
{
    Display *disp;
    XSetWindowAttributes attr;
    Window win;
    XEvent ev;
    
    disp = XOpenDisplay(NULL);
    if(!disp) return 1;

    //ウィンドウ作成

    attr.background_pixel = 0;
    attr.event_mask = ButtonPressMask | KeymapStateMask
        | KeyPressMask | KeyReleaseMask | FocusChangeMask;

    win = XCreateWindow(disp, DefaultRootWindow(disp),
        0, 0, 200, 200, 0,
        CopyFromParent, CopyFromParent, CopyFromParent,
        CWBackPixel | CWEventMask, &attr);

    XMapWindow(disp, win);

    //イベント

    while(1)
    {
        XNextEvent(disp, &ev);

        switch(ev.type)
        {
            case KeyPress:
            case KeyRelease:
                printf("- [Key%s] x(%d) y(%d) keycode(%u)\n",
                    (ev.type == KeyPress)? "Press": "Release",
                    ev.xkey.x, ev.xkey.y, ev.xkey.keycode);

                put_state(ev.xkey.state);
                fflush(stdout);
                break;
            case FocusIn:
            case FocusOut:
                printf("* [Focus%s] mode(%d) detail(%d)\n",
                    (ev.type == FocusIn)? "In": "Out",
                    ev.xfocus.mode, ev.xfocus.detail);
                fflush(stdout);
                break;
            case KeymapNotify:
                printf("# [Keymap]\n");
                fflush(stdout);
                break;
            case ButtonPress:
                goto END;
        }
    }

END:
    XCloseDisplay(disp);

    return 0;
}


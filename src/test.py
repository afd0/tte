import curses

stdscr = curses.initscr()

stdscr.clear()

stdscr.addch(0, 0, '╮')

stdscr.getkey()
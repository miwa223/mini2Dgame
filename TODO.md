
- [x] display move number in the shell at every move
- [x] window management(change to another window, minimizing)
- [x] use a 2D view(top-down or profile)
- [x] display the image in a window
    - [x] W/A/S/D key
    - [x] ESC key to close window and quit program
    - [x] red cross on the window can be used to close window and quit program
    - [x] use minilibx image
- [x] receive map
- [x] map must be closed/surrounded by walls
- [x] no need to check if there is a valid path in the map
- [x] error validation
    - [x] map
    - [x] params
- [x] memory leak

1/26W
- [x] understand tasks
- [x] get bg, sprites(hero, COLLECT, wall, exit)
    - [x] try remove black bg behind sprites -> or set the same background color

1/27T
- [x] display bg
- [x] display wall around the bg
- [x] validation - check argv[1] ".ber"
- [x] arrange sprites to the place I want

2/1T
- [x] try different map first to see if it works
- [x] git commit
- [x] deal with next to wall case -17:30
- [x] refactoring on macOS to do faster
    - [x] reconstruct struct -18:30
    - [x] rename func and variables -20:30
    - [x] file components (1hr: create directory) -21:30
    - [x] norm a little -22:30

2/2W
- [x] param validation 9:30-10:30
- [x] window management(change to another window, minimizing)
- [x] deal with bg size 10:30-12:00
- [x] memory leaks (free mlx instance?) 16:00-17:00
- [x] error handling (use strerror/perror)
    - [x] mlx's return 15:00-16:00
    - [x] map 18:15-20:00
        - [x] surrounded walls
        - [x] rectangular
        - [x] wall, COLLECT, free space, anything else are error
        - [x] 1 exit(E), 1 COLLECT(C), 1 starting position(P), wall(1) (0 doesnt have to exist)
- [x] norm 20:30-21:30

2/3T
- [x] read code from beginning thoroughly 9-10
    - [x] check ERROR MACRO
    - [x] free before return/exit
    - [x] diff between var and func name
- [x] change wall(waving sea) splite 10-10.30
- [x] test
- [x] submittion 11.30

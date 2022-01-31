
- [x] display move number in the shell at every move
- [ ] window management(change to another window, minimizing)
- [x] use a 2D view(top-down or profile)
- [ ] display the image in a window
    - [x] W/A/S/D key
    - [x] ESC key to close window and quit program
    - [x] red cross on the window can be used to close window and quit program
    - [x] use minilibx image
- [ ] receive map
- [ ] map must be closed/surrounded by walls
- [ ] no need to check if there is a valid path in the map
- [ ] error validation
    - [ ] map
    - [ ] params
- [ ] memory leak

1/26W
- [x] understand tasks
- [x] get tail, sprites(hero, collectible, wall, exit)
    - [x] try remove black tail behind sprites -> or set the same background color 

1/27T
- [x] display tail
- [x] display wall around the tail
- [ ] validation - check argv[1] ".ber"
- [ ] arrange sprites to the place I want

2/1T
- [ ] try different map first to see if it works
- [ ] git commit
- [ ] refactoring on macOS to do faster
    - [ ] rename func and variables
    - [ ] file components (1hr: create directory)
    - [ ] norm a little
- [ ] error handling (use strerror/perror)
    - [ ] map
        - [ ] number of each sprite
        - [ ] surrounded walls
        - [ ] rectangular
        - [ ] wall, collectible, free space (anything else are error)
        - [ ] 1 exit(E), 1 collectible(C), 1 starting position(P), wall(1) (0 doesnt have to exist)
    - [ ] params
    - [ ] mlx's return
- [ ] memory leaks (free mlx instance?)
- [ ] 
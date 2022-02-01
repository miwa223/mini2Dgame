
- [x] display move number in the shell at every move
- [ ] window management(change to another window, minimizing)
- [x] use a 2D view(top-down or profile)
- [ ] display the image in a window
    - [x] W/A/S/D key
    - [x] ESC key to close window and quit program
    - [x] red cross on the window can be used to close window and quit program
    - [x] use minilibx image
- [x] receive map
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
- [x] arrange sprites to the place I want

2/1T
- [x] try different map first to see if it works
- [x] git commit
- [x] deal with next to wall case -17:30
- [ ] refactoring on macOS to do faster
    - [x] reconstruct struct -18:30
    - [x] rename func and variables -20:30
    - [ ] file components (1hr: create directory) -21:30
    - [x] norm a little -22:30
- [ ] window management(change to another window, minimizing) ask someone
- [ ] deal with tail size -23:30
- [ ] error handling (use strerror/perror)
    - [ ] map -26:00
        - [ ] number of each sprite
        - [ ] surrounded walls
        - [ ] rectangular
        - [ ] wall, collectible, free space (anything else are error)
        - [ ] 1 exit(E), 1 collectible(C), 1 starting position(P), wall(1) (0 doesnt have to exist)

2/2W
    - [ ] params 10:00-11:00
    - [ ] mlx's return 11:00-12:00
- [ ] memory leaks (free mlx instance?) 13:00-14:00
- [ ] change wall splite 14:00-14:30
- [ ] norm 14:30-15:30
- [ ] submittion 16:30

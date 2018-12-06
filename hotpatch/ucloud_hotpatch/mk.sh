gcc loader.c -ldl -o loader -g
gcc patch.c -fPIC -shared -o patch.so
gcc -fPIC --shared old.c -o libold.so
gcc target.c ./libold.so -o target
gcc -fPIC --shared new.c -ldl -o libnew.so 

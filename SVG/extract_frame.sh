# Extracts all the paths in a group with id fnnn, where nnn is the frame
FRAME=$1
FRAME='id=\"f'$FRAME'\"'
awk 'BEGIN {FRAME="'$FRAME'"} {
  if($1 == "<g" && $2 == FRAME) {
     INSIDE = 1;
  } else if(INSIDE && $1 == "</g>") {
     INSIDE = 0;
  }
  if(INSIDE) {
     print;
  } 
}'
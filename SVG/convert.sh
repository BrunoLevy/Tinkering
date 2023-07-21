# converts all the paths into a .obj file
grep path | egrep -v 'transform' | \
    sed -e 's|<path d="||' -e 's|" />||' \
        -e 's|M| |g' -e 's|L| |g' -e 's|,| |g' \
   | awk '{
      for(i=1; i<NF; i+=2) {
         printf("v %f %f %f\n",$i,-$(i+1),0.0);
      }
      for(i=1; i+1<NF/2; i++) {
         printf("l %d %d\n",voffset+i, voffset+i+1);
      }
      voffset += (NF/2);
   }'     

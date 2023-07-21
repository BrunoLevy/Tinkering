# extracts frames from an animated SVG file and converts them into .obj files.
for f in 0 1 2 3 4 5 6 7 8;
do
   echo extracting frame $f
   cat Vieuxweavingloop.svg | ./extract_frame.sh $f | ./convert.sh > 'frame'$f'.obj'
done
  

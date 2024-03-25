#!/bin/bash
for f in *.png
do
echo $f
noExt=$(basename -s .png $f)
convert $noExt.png -resize 128x $noExt.png
echo $noExt
done

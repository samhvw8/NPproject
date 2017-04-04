#!/usr/bin/env sh

for filename in img/*.png; do
	fname="${filename%.*}"
	convert  -resize 50% $filename "$fname-new.png"
done

# convert  -resize 50% source.png dest.jpg
#!/usr/bin/env sh

for filename in img/*.png; do
	fname="${filename/-new/}"
	# convert  -resize 50% $filename "$fname-new.png"
	mv $filename $fname
done

# convert  -resize 50% source.png dest.jpg
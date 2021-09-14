line=$(ls -l | grep lesson | tail -1 | sed 's/.* //g')
line="'"$line"_added'"
git add ./
git commit -m $line
#git push origin
echo $line

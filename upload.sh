line=$(ls -l | grep lesson | tail -1 | sed 's/.* //g')
line="'"$line"_added'" # никак не смог сделать текст с пробелами :((
git add ./
git commit -m $line
git push origin

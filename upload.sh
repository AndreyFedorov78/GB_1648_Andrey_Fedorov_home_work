line=$(ls -l | grep lesson | tail -1 | sed 's/.* //g')
line='Добавлен файл: '$line
git add ./
git commit -a -m '$line'
git push origin

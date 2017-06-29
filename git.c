github 创建代码仓库 并 初次提交
…or create a new repository on the command line
echo "# NVR" >> README.md
git init
git add README.md
git commit -m "first commit"
git remote add origin git@github.com:yao3gang/NVR.git
git push -u origin master

…or create a new repository on the command line
echo "# NVR" >> README.md
git init
git add README.md
git commit -m "first commit"
git remote add origin https://github.com/yao3gang/NVR.git
git push -u origin master

提交
git add .
git commit -m "xxx"
git push

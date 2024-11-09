**git基本命令解释**

![image-20240913110258418](https://my-pic.miaops.sbs/2024/09/image-20240913110258418.png)

- `git restore --staged .`：移除暂存区文件，不影响本地（撤销`git add .` 操作）

- `git add -u`：将删除文件的操作同步到暂存区。将本地的删除同步到版本库（删除本地文件后执行，然后再 `git push`）
- `git rm [-r] --cached xxx`：将文件或目录从git索引中删除，不影响本地文件。通常配合`.gitignore`来删除不需要git管理的本地文件，如*.idea*，*\*/target*



**使用git add和commit添加了超过100M的大文件，导致git push报错**

![image-20240913110224120](https://my-pic.miaops.sbs/2024/09/image-20240913110224120.png)

```shell
# 1.取消本次commit(不回退工作区)
git reset HEAD~1
# 2.取消本次git add的所有文件
git restore --staged . 
# 3.将大文件添加到.gitignore

# 4.重新git add,commit,push
git add .
git commit -m "xxxx"
git push
# 5.传输大文件
git lfs install
git lfs track "dev/microService/Seata相关文件/seata-1.5.2.tar"
git add .gitattributes
git add -f "dev/microService/Seata相关文件/seata-1.5.2.tar"
git commit -m "Add seata-1.5.2.tar using Git LFS"
git push
```



**删除文件时，如何同步到远端**

```shell
# -u表示跟踪所有文件（包括被删除文件）
git add -u
git commit -m "Remove deleted files"
git push
```



**误将.idea等文件推动了，怎么删除**

```shell
# 从git索引中（暂存区和仓库）移除.idea和target
git rm -r --cached .idea
git commit -m "xxx"
git push
# 添加到.gitignore
.idea
*/target/
```



**复制已有分支到新分支开发**

注：被复制的分支代码(old-dev)，创建新的分支(new-dev)

```shell
# 1.切换到被copy的分支（new-dev），并且从远端拉取最新版本
git checkout old-dev
git pull

# 2.从当前分支，新建分支
git checkout -b new-dev

# 3.把新建的分支push到远端
git push origin new-dev

# 4. 拉取远端分支
git pull (当前的分支并没有和本地分支关联，根据提示进行下一步)

# 5.关联
git branch --set-upstream-to=origin/new-dev old-dev

# 6.再次拉取 验证
git pull
```



`new-dev`会有和`old-dev`相同的代码和提交记录，但是之后两个分支独立，**互不影响**，除非在未来把它们**合并**。

![image-20240913111150636](https://my-pic.miaops.sbs/2024/09/image-20240913111150636.png)
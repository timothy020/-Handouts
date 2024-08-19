**使用git add和commit添加了超过100M的大文件，导致git push报错**

![image-20240819090837141](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240819090837141.png)

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



**git基本命令解释**

![image-20240819101158905](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240819101158905.png)

- `git restore --staged .`：移除暂存区文件，不影响本地（撤销`git add .` 操作）

- `git add -u`：将删除文件的操作同步到暂存区。将本地的删除同步到版本库（删除本地文件后执行，然后再 `git push`）
- `git rm [-r] --cached xxx`：将文件或目录从git索引中删除，不影响本地文件。通常配合`.gitignore`来删除不需要git管理的本地文件，如*.idea*，*\*/target*


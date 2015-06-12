
```sh
#repare brew:
rm -rf ~/Library/Caches/Homebrew/ && brew update && brew upgrade --all && mkdir ~/Library/Caches/Homebrew/
```

```sh
#launch project
git clone https://github.com/Ngoguey42/Nibbler
make
export LD_LIBRARY_PATH="$HOME/.brew/lib/"
./nibbler --ui=1 -t 15 15
```

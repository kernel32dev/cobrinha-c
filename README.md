# projeto-vazio-c

Um projeto vazio para você começar seus projetos em c

Compila código c **e** c++ usando gcc e g++ no visual studio code,
`f5` funciona e é possível depurar o código, colocar breakpoints, ver variáveis etc.

## Instalação

### Linux

Caso você esteja usando linux, certifique-se que você tenha git e gcc instalado

```
git --version
gcc --version
```

Se os dois comandos acima executarem sem erros, git e gcc já estão instalados,
e você pode pular a instalação desses pacotes

A instalação depende de qual distribuição de linux você está usando,
caso seja uma distribuição baseado em Debian,
como Ubuntu, você pode usar os comandos abaixo

```
sudo apt install git-all
sudo apt install build-essential
```

Em outras distribuições, pesquise como instala git e gcc nessas outras distribuições

Então com git e gcc instalados, entre em uma pasta e clone esse repositório

```
git clone https://github.com/kernel32dev/projeto-vazio-c
```

Pronto, já deve estar funcionando, abra a pasta `projeto-vazio-c`
no vscode e aperte `f5` para ver o Hello World!

### Windows

No windows, git provavelmente não esta instalado, baixe git no site oficial: https://git-scm.com/downloads

Junto do git, será instalado o git-bash, você poderá clicar com o direito em qualquer pasta e abrir git-bash

O git-bash é um terminal onde você pode executar comandos igual no linux, recomendo bastante

No windows, gcc também provavelmente não estará instalado baixe desse site
[https://sourceforge.net/projects/mingw-w64/...](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-posix/seh/)
escolha a versão `x86_64-posix-seh`

Com o git e o mingw-w64 instalado você pode clonar o repositório, e então abrir o vscode

```
git clone https://github.com/kernel32dev/projeto-vazio-c
```

### MacOS

Eu não tenho um Mac, e não quero escrever coisas que não posso testar

Se alguem quiser contribuir as instruções com um pull request, por favor mande

Mas o processo é parecido com linux, instala git e gcc, e clona o repositório

## Executar o programa

Em python e javascript, o arquivo código fonte é lido e executado

Em c e c++, você precisa primeiro compilar cada arquivo .c e .cpp em arquivos .o, e então você precisa juntar esses vários arquivos .o em um .exe

Transformar arquivos ".c" e ".cpp" em ".o" se chama compilação, feito pelo compilador (nesse caso gcc e g++),

juntar os arquivos ".o" em um ".exe" se chama linkagem, feito pelo linker (nesse caso o g++)

Os arquivos `Makefile`, `.vscode/launch.json` e `.vscode/tasks.json` cuidam disso para você, eles vão compilar todos os arquivos dentro da pasta `src`

Para compilar o progama entre na pasta do programa (não a `src`), execute `make` para compilar o programa

Se tudo compilar sem erros, o binário vai aparecer em `dbg/a.exe`

O arquivo `Makefile` contem as instruções que o comando `make` lê para entender como compilar o progama

Você pode editar a primeira linha com `TARGET_EXEC` para mudar o nome do executável de `a` para alguma outra coisa

O exe produzido sempre terá a extensão .exe, mesmo no linux onde ela não é necessária para ter compatibilidade com o windows

E por fim, lembrando que o projeto compila tanto c como c++, você pode trocar o arquivo main.c por um main.cpp

## Erros

O processo de build não é perfeito e alguns erros estranhos podem ocorrer quando você adiciona ou remove arquivos

Quando esses erros acontecem é sempre bom executar `make clean` para apagar o cache e executar `make` ou `f5` no vscode de novo para compilar novamente

Se o erro persistir e git e gcc estiverem devidamente instalados, provavelmente é um erro no código

## Hello World

Progamas hello world em c e c++ que você pode copiar para servir como base para os seus projetos
Certifique-se que você use a extensão correta, ".c" para c e ".cpp" para c++

**main.c**:
```c++
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Hello World!\n");
}
```

**main.cpp**:
```c++
#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "Hello World!" << std::endl;
}
```

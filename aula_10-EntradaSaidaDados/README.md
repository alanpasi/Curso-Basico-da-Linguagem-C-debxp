#+title: Curso Básico da Linguagem C
#+subtitle: Aula 10: Entrada e saída de dados
#+author: Blau Araujo
#+startup: show2levels
#+options: toc:3

* Aula 10: Entrada e saída de dados

[[https://youtu.be/b6cbnZlY328][Vídeo desta aula]]

** Tabela de descritores de arquivos

Um /fluxo de dados/ (ou /stream/) é a abstração, em software, do transito de
dados entre dispositivos de hardware e processos no espaço de usuário.

Por exemplo:

- A leitura dos dados digitados no teclado do terminal;
- A impressão (ou exibição) de mensagens no /display/ do terminal;
- O acesso a um arquivo para escrita e/ou leitura de dados.

No sistema operacional, esses fluxos são estabelecidos e controlados por
diversas estruturas (/structs/), associadas individualmente a cada processo,
chamadas de /tabelas de descritores de arquivos/.

Ao serem iniciados, os processos herdam vários dados de seus respectivos
processos pais, entre eles, uma cópia da /tabela de descritores de arquivos/
representando, no mínimo, três fluxos de dados padrão.

*** Fluxos de dados padrão

Por padrão, todo processo inicia com acesso a, pelo meno, três dispositivos
ligados a um terminal:

- Entrada padrão (=/dev/stdin=): leitura da digitação no terminal;
- Saída padrão (=/dev/stdout=): exibição de mensagens no terminal;
- Saída padrão de erros (=/dev/stderr=): exibição de mensagens de erros no terminal.

Cada um desses dispositivos padrão é disponibilizado para cada processo,
individualmente, através de uma entrada na sua tabela de descritores de
arquivos:

- =stdin=: descritor de arquivos =0=;
- =stdout=: descritor de arquivos =1=;
- =stderr=: descritor de arquivos =2=.

*** Uma nota sobre dispositivos

Sistemas parecidos com o UNIX geralmente trabalham com 7 tipos de arquivos:

- Diretórios: arquivos que indexam a localização de outros arquivos;
- Arquivos comuns: como os arquivos dos nossos textos, programas e imagens;
- Ligações simbólicas: arquivos que representam outros arquivos;
- Dispositivos caractere: abstração da comunicação com dispositivos de
  hardware sem o acúmulo de dados;
- Dispositivos bloco: abstração da comunicação com dispositivos de hardware
  com acúmulo de dados;
- Pipes/FIFOs: arquivos que interfaceiam a troca de dados entre processos;
- Sockets: arquivos de interfaceiam o acesso a serviços.

Então, quando dizemos algo como: /"dispositivo de terminal"/, ou /"dispositivo
padrão de entrada"/ (ou de saída), nós estamos falando de um desses tipos de
arquivos.

*** Representação em /proc

Como vimos na [[https:../08-processos#headline-8][aula 8]], o kernel disponibiliza todas as informações sobre todos
os processos em execução na forma de um sistema de arquivos virtual (=procfs=)
montado no diretório =/proc=. Nele, cada processo terá um subdiretório nomeado
segundo seu número de identificação (PID) e, neste subdiretório, existe um
outro subdiretório com as ligações simbólicas entre os descritores de arquivos
do processo e os arquivos e dispositivos a que ele tem acesso: é o diretório
=/proc/PID/fd=.

Se listarmos, por exemplo, o diretório =fd= do processo do shell, nós veremos
algo assim:

#+begin_example
$ ls -l /proc/$$/fd
total 0
lrwx------ 1 blau blau 64 abr 23 08:09 0 -> /dev/pts/1
lrwx------ 1 blau blau 64 abr 23 08:09 1 -> /dev/pts/1
lrwx------ 1 blau blau 64 abr 23 08:09 2 -> /dev/pts/1
lrwx------ 1 blau blau 64 abr 23 08:09 255 -> /dev/pts/1
#+end_example

#+begin_quote
Aqui, =$$= é a expansão do parâmetro especial do shell que contém o número
do seu processo.
#+end_quote

Observe que os três descritores de arquivos padrão (=0=, =1= e =2=) estão
presentes como ligações simbólicas (outro tipo de arquivo) para o mesmo
dispositivo de terminal (=/dev/pts/1=).

*** Um exemplo em C

Com a função =system=, declarada no cabeçalho =stdlib.h=, nós podemos executar
o utilitário =ls= para listar os descritores de arquivos atribuídos ao processo
iniciado para a execução do nosso programa (=fdlist.c=):

#+begin_src c
#include <stdlib.h>

int main(void) {
    system("ls -l /proc/$(pidof a.out)/fd");
    return 0;
}
#+end_src

#+begin_quote
O utilitário =pidof= exibe o número do PID de um processo a partir do
nome do programa que o iniciou passado como argumento: no caso, o nosso
=a.out=. 
#+end_quote

Compilando e executando:

#+begin_example
:~$ gcc -Wall fdlist.c
:~$ ./a.out
total 0
lrwx------ 1 blau blau 64 abr 23 08:16 0 -> /dev/pts/1
lrwx------ 1 blau blau 64 abr 23 08:16 1 -> /dev/pts/1
lrwx------ 1 blau blau 64 abr 23 08:16 2 -> /dev/pts/1
#+end_example

Repare que, como o processo foi iniciado pela mesma sessão do shell do
exemplo anterior, nós temos os três descritores de arquivos padrão ligados
ao mesmo terminal de antes (=/dev/pts/1=). Isso aconteceu porque esses
fluxos de dados foram herdados do processo pai (o processo do shell).

** Redirecionamentos e pipes

Também na [[https://bolha.dev/blau_araujo/cblc/src/branch/main/aulas/08-processos#headline-6][aula 8]], nós vimos que as linhas de comandos simples podem conter
operadores de redirecionamento de fluxos de dados de/para arquivos, ou
ainda, poderiam ser encadeados com outros comandos simples através do
operador de /pipe/.

*** Redirecionamentos

Quando um fluxo de dados é redirecionado, por exemplo, para ler um arquivo,
o que é feito com o operador de redirecionamento de leitura (=<=), a ligação
do descritor de arquivos =0= (=stdin=) passa a ser feita com o arquivo.

Por exemplo, se eu tiver um arquivo chamado =lista.txt= e redirecionar seu
conteúdo para leitura pelo programa do exemplo anterior, o resultado seria
esse:

#+begin_example
:~$ ./a.out < lista.txt
total 0
lr-x------ 1 blau blau 64 abr 23 08:47 0 -> /home/blau/lista.txt
lrwx------ 1 blau blau 64 abr 23 08:47 1 -> /dev/pts/1
lrwx------ 1 blau blau 64 abr 23 08:47 2 -> /dev/pts/1
#+end_example

Já se eu quisesse escrever a saída do programa em um arquivo, bastaria
fazer um redirecionamento de escrita (operadores =>= ou =>>=):

#+begin_example
:~$ ./a.out > lista.txt
:~$ cat lista.txt
total 0
lrwx------ 1 blau blau 64 abr 23 08:49 0 -> /dev/pts/1
l-wx------ 1 blau blau 64 abr 23 08:49 1 -> /home/blau/lista.txt
lrwx------ 1 blau blau 64 abr 23 08:49 2 -> /dev/pts/1
#+end_example

Como eu redirecionei a saída padrão do programa para um arquivo, nada foi
mostrado no terminal e, por isso, eu exibi o conteúdo do arquivo com o
utilitário =cat=.

*** Pipes

Com os pipes é semelhante, mas nós teríamos uma ligação com outro processo
interfaceada por um arquivo do tipo /pipe/ criado pelo sistema.

Por exemplo, eu posso encadear o nosso programa de exemplo em um pipe com
o utilitário =cat=:

#+begin_example
:~$ ./a.out | cat
total 0
lrwx------ 1 blau blau 64 abr 23 08:56 0 -> /dev/pts/1
l-wx------ 1 blau blau 64 abr 23 08:56 1 -> pipe:[2551457]
lrwx------ 1 blau blau 64 abr 23 08:56 2 -> /dev/pts/1
#+end_example

Aqui, a saída do nosso programa (descritor de arquivos =1=) está ligada
ao arquivo =pipe:[2551457]= para escrita. Ao mesmo tempo, o processo do
=cat= teria a sua entrada padrão (descritor de arquivos =0=) ligada ao mesmo
arquivo para leitura.

Eu posso até modificar meu programa para exibir os diretórios =fd= dos dois
processos:

#+begin_src c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    puts("Processo do programa:");
    fflush(stdout);
    system("ls -l /proc/$(pidof a.out)/fd");

    puts("\nProcesso do cat:");
    fflush(stdout);
    system("ls -l /proc/$(pidof cat)/fd");
    return 0;
}
#+end_src

Compilando e executando com o pipe novamente:

#+begin_example
:~$ gcc -Wall fdlist.c
:~$ ./a.out | cat
Processo do programa:
total 0
lrwx------ 1 blau blau 64 abr 23 09:06 0 -> /dev/pts/1
l-wx------ 1 blau blau 64 abr 23 09:06 1 -> pipe:[2550676]
lrwx------ 1 blau blau 64 abr 23 09:06 2 -> /dev/pts/1

Processo do cat:
total 0
lr-x------ 1 blau blau 64 abr 23 09:06 0 -> pipe:[2550676]
lrwx------ 1 blau blau 64 abr 23 09:06 1 -> /dev/pts/1
lrwx------ 1 blau blau 64 abr 23 09:06 2 -> /dev/pts/1
#+end_example

** Acumuladores (buffers)

Na última versão do exemplo, eu precisei chamar a função =fflush(stdout)=,
e veja o que aconteceria sem ela:

#+begin_src c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    puts("Processo do programa:");
    system("ls -l /proc/$(pidof a.out)/fd");

    puts("\nProcesso do cat:");
    system("ls -l /proc/$(pidof cat)/fd");
    return 0;
}
#+end_src

Compilando e executando:

#+begin_example
:~$ gcc -Wall fdlist.c
:~$ ./a.out | cat
total 0
lrwx------ 1 blau blau 64 abr 23 09:12 0 -> /dev/pts/1
l-wx------ 1 blau blau 64 abr 23 09:12 1 -> pipe:[2569607]
lrwx------ 1 blau blau 64 abr 23 09:12 2 -> /dev/pts/1
total 0
lr-x------ 1 blau blau 64 abr 23 09:12 0 -> pipe:[2569607]
lrwx------ 1 blau blau 64 abr 23 09:12 1 -> /dev/pts/1
lrwx------ 1 blau blau 64 abr 23 09:12 2 -> /dev/pts/1
Processo do programa:

Processo do cat:
#+end_example

Notou que as linhas impressas pela função =puts= só foram exibidas depois
das listagens feitas pela função =system=?

Isso aconteceu porque, *em um pipe*, a saída do programa é /totalmente bufferizada/,
ou seja, os dados impressos por funções como =puts= e =printf= são acumuladas
no /buffer de saída/ do processo, mas não podem ser despejadas imediatamente
na saída padrão até que outros subprocessos o façam. Como nós temos as
chamadas da função =system=, que iniciam subprocessos para executar comandos,
as listagens dos diretórios são despejadas e só depois as linhas das chamadas
de =puts= são despejadas.

Isso não aconteceria se não houvesse um pipe:

#+begin_src c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    puts("Processo do programa:");
    system("ls -l /proc/$(pidof a.out)/fd");

    puts("\nProcesso do cat:");
    system("ls -l /proc/$(pidof cat)/fd");
    return 0;
}
#+end_src

Compilando e executando:

#+begin_example
:~$ gcc -Wall fdlist.c
:~$ ./a.out
Processo do programa:
total 0
lrwx------ 1 blau blau 64 abr 23 09:21 0 -> /dev/pts/1
lrwx------ 1 blau blau 64 abr 23 09:21 1 -> /dev/pts/1
lrwx------ 1 blau blau 64 abr 23 09:21 2 -> /dev/pts/1

Processo do cat:
ls: não foi possível acessar '/proc//fd': Arquivo ou diretório inexistente
#+end_example

Ignorando o erro (o =cat= não estava em execução), veja que as linhas foram
impressas na ordem em que apareciam no programa, sem a função =fflush=. Isso
porque, sem pipes ou redirecionamentos ocupando a saída padrão, o /buffer de
saída/ do programa é liberado /linha a linha/ (na ocorrência do caractere de
quebra de linha =\n=). Mas, com um redirecionamento, por exemplo...

#+begin_example
:~$ ./a.out > lista.txt
ls: não foi possível acessar '/proc//fd': Arquivo ou diretório inexistente
:~$ cat lista.txt
total 0
lrwx------ 1 blau blau 64 abr 23 09:38 0 -> /dev/pts/1
l-wx------ 1 blau blau 64 abr 23 09:38 1 -> /home/blau/lista.txt
lrwx------ 1 blau blau 64 abr 23 09:38 2 -> /dev/pts/1
Processo do programa:

Processo do cat:
#+end_example

#+begin_quote
*Nota:* veja que a mensagem de erro não foi escrita no arquivo, mas foi exibida
no terminal, porque ela foi enviada através da /saída padrão de erros/ (=stderr=).
#+end_quote

O que a função =fflush= faz, com o fluxo de dados =stdout= como argumento, é
forçar a descarga do que houver no buffer de saída do programa, independente
de haver pipes ou redirecionamentos.

*** Buffers de entrada e saída do programa

Voltando um pouco o assunto, algumas funções da =libc/glibc= alocarão
algum espaço no /heap/ do processo do programa para acumular dados recebidos
pela entrada padrão ou destinados à saída padrão.

Por exemplo:

- Produzem um buffer de saída: funções =puts=, =printf=, etc;
- Produzem um buffer de entrada: funções =scanf=, =fgets=, etc. 

*** Buffer de saída do programa

No caso do buffer de saída, como vimos, o tipo de acumulação é determinado,
entre outras coisas, pela eventualidade de algum pipe ou redirecionamento:

- *Bufferização linha a linha:* programa executado sem pipes ou redirecionamentos.
- *Bufferização total:* programa executado em um pipe ou com redirecionamentos.
- *Sem bufferização:* com chamadas de sistema (ex: =write=) ou quando configurado
  explicitamente.

*** Buffer de entrada do programa

De certo modo, a acumulação de dados lidos de arquivos ou do terminal são
mais simples, ou melhor, não estão sujeitos a tantas condições como o
buffer de saída, mas também têm as suas particularidades.

Com a funções como =scanf= e =fgets=, a entrada é bufferizada e todos os bytes
recebidos são acumulados. No entanto, caberá às características de cada
função determinar como esses dados serão consumidos no programa.

Por exemplo, se utilizarmos as funções =scanf= ou =fgets= para ler algo digitado
no terminal (entrada interativa), pode ser que, de tudo que for digitado,
apenas uma parte seja consumida, fazendo com que reste alguma coisa no
buffer de entrada. Os dados restantes poderão vir a ser consumidos nas
chamadas subsequentes dessas funções, com resultados bastante inconvenientes!

Como a =glibc= não possui uma função para consumir os dados restantes no
buffer de entrada após uma leitura, é comum utilizarmos algo assim depois
da chamada de uma função com entrada bufferizada (se a leitura for da
entrada padrão):

#+begin_src c
int ch;
while ((ch = getchar()) != '\n' && ch != EOF);
#+end_src

#+begin_quote
Nas próximas aulas, nós falaremos das particularidades da leitura da
entrada padrão com as funções =scanf= e =fgets=.
#+end_quote

*** Entrada padrão não bufferizada

Quando a entrada padrão não é bufferizada, nós ficamos sujeitos às regras
de bufferização do lado do sistema: em especial, o buffer do dispositivo
de terminal.

Por exemplo, numa leitura interativa com a chamada de sistema =read=, onde nós
limitamos a quantidade de bytes que serão consumidos, pode restar algo do que
foi digitado no buffer do terminal e, se o nosso programa não consumir esses
bytes excedentes, eles serão descarregados na saída padrão pelo próprio terminal,
quando o processo do nosso programa terminar, e serão lidos pelo shell como
se fosse um comando.

Nas próximas três aulas, nós vamos explorar a leitura interativa de dados
digitados no terminal e todas essas particularidades serão demonstradas.



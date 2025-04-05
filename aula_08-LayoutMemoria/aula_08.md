# Curso Básico da Linguagem C - Aula #8: Layout de memória
#### https://youtu.be/60bXYVCFoTI

#+title: Curso Básico da Linguagem C
#+subtitle: Aula 8: Processos
#+author: Blau Araujo
#+startup: show2levels
#+options: toc:3

* Aula 8: Processos e layout de memória

[[https://youtu.be/60bXYVCFoTI][Vídeo desta aula]]

** Filosofia UNIX

Doug McIlroy, que implementou o conceito de /pipes/ no Unix, resumiu a /filosofia
UNIX/ em três princípios:

- /Escreva programas que façam apenas uma coisa, mas que a façam bem feita./
- /Escreva programas que trabalhem juntos./
- /Escreva programas que manipulem fluxos de texto, pois esta é uma interface universal./

Se repararmos bem, esses princípios de caracterizam perfeitamente o
desenvolvimento do sistema operacional Unix e a forma como ele foi projetado
para ser operado.

*Lembre-se...*

Os sistemas operacionais parecidos com o Unix (/Unix-like/) podem ser descritos
através de seus quatro conjuntos de softwares mais essenciais, o que também se
aplica ao nosso GNU/Linux:

| Componente                     | Unix/Unix-like                         | GNU/Linux     |
|--------------------------------+----------------------------------------+---------------|
| Kernel                         | Unix Kernel, BSD Kernel, etc...        | Linux         |
| Biblioteca C padrão            | =libc=                                   | =glibc=         |
| Shell                          | =sh=                                     | =bash=          |
| Utilitários da base do sistema | Programas como: =cat=, =grep=, =sed=, etc... | GNU Coreutils |

*** Primeiro princípio: especialização

#+begin_quote
/Escreva programas que façam apenas uma coisa, mas que a façam bem feita./
#+end_quote

*Separação de atribuições...*

No escopo do sistema como um todo, nós podemos relacionar esse princípio
com a separação entre o /espaço do kernel/ e o /espaço de usuário/:

- *Espaço do kernel:* região de memória onde o kernel do sistema operacional
  executa e tem acesso privilegiado a todos os recursos de hardware e software.

- *Espaço do usuário:* região de memória onde os /processos/ dos programas são
  executados com permissões restritas e têm o acesso ao hardware intermediado
  pelo kernel.

*Criação de programas...*

Para a escrita de programas, nós temos a =libc=, que abstrai as chamadas às
funções internas do kernel (/chamadas de sistema/, ou /syscalls/) e centenas
de outras funcionalidades.

*Interface padrão de operação...*

Mesmo no espaço de usuário, o /shell/ se diferencia dos demais programas da
base do sistema porque, em princípio, é somente através dele que os outros
programas são executados pelo /usuário/.

#+begin_quote
O /shell/ é a interface padrão entre o sistema e o usuário que, através de linhas
de comandos em texto, declara o que quer que seja executado.
#+end_quote

*Programas para diversas tarefas úteis...*

Finalmente, o usuário tem acesso a dezenas de utilitários da base do sistema,
cada um com a sua especialidade, para a realização de inúmeros tipos de
tarefas.

*** Segundo princípio: modularidade

#+begin_quote
/Escreva programas que trabalhem juntos./
#+end_quote

Com a especialização, vem a necessidade de fazer com que cada componente do
sistema, de acordo com suas atribuições, seja projetado para trabalhar com
outros programas.

*Linha de comandos...*

Para operar o sistema, o usuário tem acesso a um terminal onde seus comandos
poderão ser digitados e enviados para o shell:

#+begin_example
  +---------+      +----------+      +---------+      +--------+
  | TECLADO | ---→ |          | ---→ |  SHELL  | ---→ | KERNEL |
  +---------+      |          |      +---------+      +--------+
                   | TERMINAL |                           ↑
  +---------+      |          |      +---------------+    |
  | MONITOR | ←--- |          | ←--→ | NOVO PROCESSO | ←--+
  +---------+      +----------+      +---------------+
#+end_example

Quando o shell recebe a linha de um comando, ele interpreta o que foi
digitado e, se for o caso, faz uma /chamada de sistema/ =fork= para que
o kernel crie uma cópia (/clone/) de seu processo. Em seguida, no processo
clonado, o shell faz uma chamada de sistema =exec=, para que o kernel
substitua parte dos dados copiados do processo do shell pelos dados
do programa que será executado.

*Tarefas complexas...*

Cada utilitário da base do sistema é construído segundo o conceito de
/interface de linha de comando/, ou CLI. Isso quer dizer que, além das
suas especialidades, cada um deles é capaz de trocar dados com outros
programas para que o usuário, a partir de programas simples, seja
capaz de realizar tarefas complexas.

Por exemplo, digamos que você tenha um arquivo com uma lista de
pedidos e queira filtrar as compras realizadas em um dado mês. Você
poderia utilizar o programa =grep=, que é especializado em localizar
e imprimir linhas de texto a partir de padrões descritos por
expressões regulares:

#+begin_example
:~$ grep '03/2025' pedidos.data
"Maria das Couves", "02/03/2025", "2564", "Porta copos"
"Antônio dos Santos", "09/03/2025", "7544", "Toalha de mesa"
"João da Silva", "01/03/2025", "3762", "Jogo de 12 talheres"
#+end_example

Se, além das linhas impressas, você precisar ordenar o resultado
pelos nomes dos clientes, o =grep= será insuficiente sozinho, mas
você pode recorrer ao utilitário =sort= para processar a saída
produzida pelo =grep= escrevendo apenas um comando:

#+begin_example
:~$ grep '03/2025' pedidos.data | sort
"Antônio dos Santos", "09/03/2025", "7544", "Toalha de mesa"
"João da Silva", "01/03/2025", "3762", "Jogo de 12 talheres"
"Maria das Couves", "02/03/2025", "2564", "Porta copos"
#+end_example

*** Terceiro princípio: fluxos de texto

#+begin_quote
/Escreva programas que manipulem fluxos de texto, pois esta é uma interface universal./
#+end_quote

Como vimos, até aqui...

- 0 terminal recebe um fluxo de caracteres digitado em um teclado e envia
  para o shell;
- O shell interpreta o texto recebido e monta textos correspondendo aos
  argumentos que serão passados para as chamadas de sistema;
- O kernel executa a chamada de sistema e cria um novo processo para
  executar o programa que foi invocado... Mas não é só isso!

Além dos dados do programa (basicamente, o conteúdo de seu binário),
o novo processo incluirá outros dados que já estavam registrados no
processo do shell:

- A quantidade de palavras utilizadas para invocar o programa;
- A lista das palavras utilizadas para invocar o programa;
- Uma lista das variáveis que serão herdadas pelo novo processo;
- Uma lista de arquivos padrão que poderão ser utilizados para enviar
  e receber fluxos de texto.

Sendo assim...

- As palavras utilizadas para invocar o programa são chamadas de /argumentos
  de linha de comando/.
- A lista de variáveis herdadas pelo programa irão compor um /ambiente de
  dados/ que poderão ser utilizados pelo programa.
- A lista de arquivos padrão para receber e enviar fluxos de caracteres para
  o terminal são os /descritores de arquivos padrão/: =stdin= (entrada padrão),
  =stdout= (saída padrão) e =stderr= (saída padrão de erros).

Mas existem mecanismos no kernel que possibilitam o desvio dos fluxos de
dados padrão para outros arquivos. Assim, se eu quiser enviar a saída do
meu programa para um arquivo, em vez de para o terminal, eu posso redirecionar
a saída padrão (=stdout=, descritor de arquivos =1=) para esse arquivo:

#+begin_example
ls -l > arquivos.txt
#+end_example

Do mesmo modo, eu poderia desviar a saída padrão de um programa para a
entrada padrão de outro programa. Para isso, o kernel precisaria criar
um outro tipo de arquivo, chamado de /pipe/, para canalizar o fluxo de
texto entre os dois programas. Na linha de comandos...

#+begin_example
:~$ grep '03/2025' pedidos.data | sort
#+end_example

Nesse caso, os dois programas são executados ao mesmo tempo e, enquanto
o primeiro envia dados para um /pipe/, o segundo lê este mesmo arquivo:

#+begin_example
  +-----------------------------+      +------+      +------+
  | grep '03/2025' pedidos.data | ---> | PIPE | ---> | sort |
  +-----------------------------+      +------+      +------+
#+end_example

Assim que o =grep= terminar o envio de linhas de texto, o =sort= será terminado.

** A interface de linha de comando (CLI)

A filosofia Unix nos ajuda a compreender, de um modo mais amplo, como os
sistemas /Unix-like/ foram pensados para lidar com o hardware, possibilitarem
a criação e execução de programas e serem operados. Especialmente quanto à
operação do sistema pela linha de comandos, são as convenções da /interface
de linha de comandos/ (CLI), implementada no shell, que determinam como
os programas e o sistema deverão lidar com os nossos comandos.

Um comando simples, seque este esquema geral:

#+begin_example
[EXPORTAÇÕES] [INVOCAÇÃO] [ARGS...] [REDIRECIONAMENTO ARQUIVO]
#+end_example

- *Exportações:* uma ou mais variáveis que serão exportadas para o ambiente
  do processo do programa executado.
- *Invocação:* o caminho e o nome do programa que será executado.
- *Argumentos:* lista de palavras que serão passadas para o processo do
  programa como opções ou informações adicionais.
- *Redirecionamento:* através de operadores do shell, a saída do programa
  pode ser desviada para um arquivo ou um arquivo poderá ser informado
  para ser lido e processado pelo programa.

#+begin_quote
A /invocação/ (o caminho e o nome do programa) sempre será o primeiro argumento
da lista de argumentos.
#+end_quote

*** Operadores de controle do shell

Quando a linha de um comando contém a invocação de mais de um programa,
é necessário estabelecer como essas invocações se relacionam, o que é
feito com os /operadores de controle/ do shell:

- *Encadeamento incondicional* (=;= ou =\n=): O comando seguinte será executado após o
  término do anterior.

- *Encadeamento assíncrono* (=&=): O comando seguinte será executado em paralelo com
  o anterior e em segundo plano.

- *Encadeamento condicional "se sucesso"* (=&&=): O comando seguinte só será
  executado se, e quando, o último comando executado terminar com sucesso.

- *Encadeamento condicional "se erro"* (=||=): O comando seguinte só será executado
  se, e quando, o último comando executado terminar com erro.

- *Encadeamento por pipe* (=|=): Os comandos serão executados em paralelo e a saída
  do primeiro será canalizada para a entrada do segundo.

** O que são processos

Um processo é um conjunto de estruturas de dados que o kernel utiliza para
gerenciar a execução de programas. No centro dessas estruturas de dados está uma
faixa virtual contínua de endereços de memória que o kernel designará para cada
programa em execução. Essa faixa virtual de endereços de memória, também chamada
de /memória virtual/ ou /espaço de endereços/, representa toda a memória disponível
a que o processo do programa terá acesso.

Além disso, o kernel disponibiliza todas as informações sobre todos os processos
em execução na forma de um sistema de arquivos virtual (/procfs/) montado no
diretório =/proc=. Nele, cada processo terá um subdiretório nomeado segundo seu
número de identificação (PID).

** Como programas são executados

Para o sistema operacional, /executar um programa/ significa criar um novo processo
e designar um espaço de memória para ele. Para chegar a este ponto, o programa terá
que ser invocado por outro programa já em execução (/processo pai/, geralmente o shell)
que, através de duas chamadas de sistema responsáveis por (chamada =fork=) criar uma
duplicata do processo pai (um /clone/) como um novo processo e depois substituir parte
dos dados no espaço de memória dessa duplicata pelos dados encontrados no binário
do programa que será executado.

Aqui está um exemplo em C que mostra. simplificadamente, a execução de outro programa:

#+begin_src c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    // Chamada fork...
    pid_t pid = fork();

    // Se o fork falhar...
    if (pid < 0) {
        perror("fork falhou");
        exit(EXIT_FAILURE);
    }

    /*
    Um segundo processo é criado e o código seguinte será executado
    por ambos os processos (eles são idênticos!), mas com valores
    de pid diferentes:

    - Para o processo filho, pid == 0
    - Para o processo pai, pid == PID do processo filho

    Por isso temos essa estrutura if...
    */
    if (pid == 0) {
        // Processo filho...
        printf("[Filho] PID: %d, iniciado.\n", getpid());
        char *args[] = {"ls", "-l", NULL};
        // Chamada exec (execvp)...
        execvp(args[0], args);
        // Se execvp falhar...
        perror("execvp falhou");
        exit(EXIT_FAILURE);
    } else {
        // Processo pai...
        printf("[Pai] PID: %d, criou filho PID: %d\n", getpid(), pid);
        printf("[Pai] Aguardando término do filho...\n");
        int status;
        waitpid(pid, &status, 0);
        printf("[Pai] Processo filho %d terminou com status %d\n", pid, WEXITSTATUS(status));
        printf("[Pai] Voltando ao controle.\n");
    }

    return 0;
}
#+end_src

Compilando e executando:

#+begin_example
:~$ gcc -Wall exemplo.c
:~$ ./a.out
[Pai] PID: 1810185, criou filho PID: 1810186
[Pai] Aguardando término do filho...
[Filho] PID: 1810186, iniciado.
total 56
-rwxrwxr-x 1 blau blau 16280 mar 22 08:00 analise
-rw-rw-r-- 1 blau blau  1549 mar 22 08:05 analise.c
-rwxrwxr-x 1 blau blau 16304 mar 30 11:37 a.out
-rw-rw-r-- 1 blau blau   594 mar 22 11:22 exemplo.c
-rw-rw-r-- 1 blau blau   325 mar 22 10:45 fizzbuzz.c
-rw-rw-r-- 1 blau blau  1743 mar 17 21:32 limites.c
-rw-rw-r-- 1 blau blau   340 mar 20 14:33 str.c
-rw-rw-r-- 1 blau blau   882 mar 30 11:37 teste.c
[Pai] Processo filho 1810186 terminou com status 0
[Pai] Voltando ao controle.
#+end_example

#+begin_quote
No GNU/Linux, o shell chama a /syscall/ =clone=, em vez de =fork=, e =execve=,
em vez de =execvp=.
#+end_quote

** Layout de memória

Quando o processo é iniciado, ele recebe uma faixa contínua de endereços /virtuais/
de memória, segundo o layout abaixo:

#+begin_example
      ENDEREÇOS MAIS ALTOS
  +--------------------------+ ---+
  |      Vetor Ambiente      |    |
  +--------------------------+    |
  |     Vetor Argumentos     |    |
  +--------------------------+  PILHA (STACK)
  | Quantidade de argumentos |    |
  +--------------------------+    |
  |    Dados das funções     |    |
  +------------+-------------+ ---+
  |            ↓             |
  |                          |
  |            ↑             |
  +------------+-------------+
  |                          |  <- Mapeamento de arquivos.
  |           HEAP           |  <- Bibliotecas dinâmicas.
  |                          |  <- Alocação dinâmica.
  +--------------------------+
  |         .bss             |  Dados globais e estáticos não inicializados.
  +--------------------------+
  |         .data            |  Dados globais e estáticos inicializados.
  +--------------------------+
  |        .rodata           |  Dados constantes (read only).
  +--------------------------+
  |         .text            |  Código do programa.
  +--------------------------+
     ENDEREÇOS MAIS BAIXOS
#+end_example

*** Conteúdo do binário executável

As seções do binário do executável serão copiadas para os segmentos
mais baixos desse espaço de endereços.

*** Região do HEAP

Acima dos dados do binário, uma grande região é designada para a alocação
dinâmica de espaços em memória para receber dados processados durante a execução
do programa: o /heap/. Nesta mesma região, também são carregados os conteúdos
binários das bibliotecas carregadas dinamicamente, como a =glibc=, o =ld-linux= e
a biblioteca =vdso=, do kernel.

*** Região da pilha (stack)

Nos endereços mais altos, é configurada uma estrutura de dados chamada /pilha/.
Como o nome sugere, é uma estrutura onde os dados são "empilhados" uns sobre os
outros, como numa pilha de pratos.

Na base da pilha, nós encontramos um vetor de strings contendo as variáveis
exportadas para o processo (vetor ambiente). Imediatamente acima, nós temos
outro vetor de strings com as palavras utilizadas na linha do comando para
invocar a execução do programa e, eventualmente, seus argumentos (vetor de
argumentos ou /parâmetros/). Por último, no topo da pilha, nós encontraremos
a quantidade de palavras no vetor de argumentos.

Ao longo da execução do programa, os dados das funções que forem chamadas
serão incluídos no topo da pilha e serão removidos quando elas terminarem.

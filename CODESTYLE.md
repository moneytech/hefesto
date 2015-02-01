Codestyle
---------

If you want to contribute with this project, I follow this codestyle:

    * Codes with columns limited in 80-120 bytes
    * White spaces are used to separate the code in logical blocks, save your disorder for the next ioccc
    * #pragmas are forbidden
    * include guards need to be defined with 1 -> #define _EXAMPLE_H 1
    * if/else, while and for blocks are K&R based
    * Indentation deepness: 8 spaces
    * Use 0 as string delimitator instead of '\0'
    * Use NULL to represent null pointers
    * Do not use ultraExplainedBoringNames, you're an C programmer, honor it or do a harakiri...
    * Static functions need to be prototyped at the module beginning
    * Pointers declaration: "void *vptr = NULL;" and not: "void* vptr = NULL;"

This is the way that if blocks are written:

    if (6 == 9) {
        printf("I don't mind!\n");
    } else {
        printf("I don't care!\n");
    }

Avoid this type of construction:

    if (6 == 9)
        printf("I don't mind!\n");
    else
        printf("I don't care!\n");

For while you use:

    int i = 99;
    while (i-- > 0) {
        printf("%d %s of beer on the wall.\n", i, (i > 1) ? "bottle" :
                                                           "bottles");
    }

This is the way to write for blocks:

    for (i = 99; i > 0; i--) {
        printf("%d %s of beer on the wall.\n", i, (i > 1) ? "bottle" :
                                                           "bottles");
    }

The way for switches is:

    switch (c) {

        case 0:
            //  do something
            break;

        case 1:
            //  do something
            break;

        default:
            //  do something
            break;

    }

Best practices
--------------

    * Give credit to yourself and keep the credit from others
    * If you created a new feature be ready to include an acceptable documentation in your pull request
    * If you wish to create a new thing try to turn it possible in a straightforward way
    * Always seek to kill bugs in this way: "K.I.S.S! K.I.S.S! Bang! Bang!"
    * What K.I.S.S does mean? Thank you, but goodbye!
    * Write tests
    * Don't trust in the unit tests only, build the application and *** always *** use it
    * Don't write crazy tests that in the future will make impossible needed fixes due to perform tests
      under impossible situations
    * Learn with musicians which read transcriptions from other musicians, create the code reading habit
      seeking to learning and not only for refactory issues
    * I'm brazilian and I write comments in portuguese, if you speak portuguese too and wish to comment with this language,
      include if possible an english version of your comment
    * Your ideas and specialities in some subject is what are welcome in this project, these things need to
      stay even if you have gotten away, have been abducted or have gone to write code in BASIC, never retain information.
      In this way your mind can produce more things here and in other places

Codestyle
---------

Se voc� quiser contribuir com o projeto, eu adoto o seguinte codestyle:

    * C�digos limitados a 80-120 colunas
    * C�digos separados em blocos l�gicos, guarde sua desordem para o pr�ximo ioccc
    * #pragmas n�o s�o permitidos
    * include guards precisam ser definidos com 1 -> #define _EXAMPLE_H 1
    * Blocos if/else, while e for s�o baseados no K&R
    * Endenta��o: 8 espa�os
    * Use 0 para determinar final de string, n�o '\0'
    * Use NULL para representar pointeiros nulos
    * N�o use nomesSuperExplicadosLongosAlemDeMuitoEntediantesDeLer, voc� programa em C, honre isso ou se honre cometendo imediatamente um harakiri. ;D
    * Prototipe todas as fun��es est�ticas no in�cio do m�dulo
    * Declara��o de ponteiros: "void *vptr = NULL;" e n�o: "void* vptr = NULL;" 
    
Assim fica um bloco If:

    if (1 == 0) {
        printf("Tudo que era s�lido j� derreteu!\n");
    } else {
        printf("Tudo que � s�lido pode derreter!\n");
    }

Evite esse tipo de constru��o:

    if (1 == 0)
        printf("Tudo que era s�lido j� derreteu!\n");
    else
        printf("Tudo que � s�lido pode derreter!\n");
        
No while voc� usa:

    int i = 0;
    while (i++ > 1000) {
        printf("%d %s muita gente %d elefantes incomodam mto mais.\n", i, (i > 1) ? "elefantes incomodam" :
                                                                                    "elefante incomoda", i+1);
    }

No for � assim:

    for (i = 1; i < 1000; i++) {
        printf("%d %s muita gente %d elefantes incomodam mto mais.\n", i, (i > 1) ? "elefantes incomodam" :
                                                                                    "elefante incomoda", i+1);
    }
    
Switch � assim:

    switch (c) {
    
        case 0:
            //  do something
            break;
            
        case 1:
            //  do something
            break;
            
        default:
            //  do something
            break;
            
    }

Boas pr�ticas
-------------

    * Se d� cr�dito e mantenha o cr�dito dos outros
    * Se criou uma nova feature esteja pronto a incluir uma documenta��o aceit�vel no seu push request
    * Se quiser criar algo novo tente possibilitar o resultado do jeito mais direto poss�vel, o usu�rio
      n�o chama Ulisses para ter que passar um perrengue danado para alcan�ar o objetivo, n�s
      desenvolvedores que temos que ser Ulisses o suficiente para fazer o dif�cil ridiculamente f�cil
      para o usu�rio *** interessado ***
    * Sempre busque matar bugs dessa forma: "K.I.S.S! K.I.S.S! Bang! Bang!"
    * Escreva testes
    * N�o confie apenas nos unit tests, construa o aplicativo e use-o *** sempre ***
    * N�o escreva testes malucos que no futuro impossibilitar�o fixes por conta de testarem situa��es
      anti-f�sicas (que nunca ir�o ocorrer na pr�tica no universo do aplicativo), melhor n�o ter teste
      do que ter um teste assim
    * Aprenda com os m�sicos que le�m partituras de outros m�sicos, crie o h�bito de ler o c�digo dos outros
      n�o s� para dar refactory mas para aprender
    * Sou brasileiro e me dou ao luxo de comentar em portugu�s, se voc� tamb�m fala portugu�s e quiser comentar
      com esse idioma bacana, inclua a vers�o do coment�rio tamb�m em ingl�s se poss�vel
    * Suas ideias e especialidade em algum assunto � que s�o bem-vindas ao projeto, essas coisas precisam se
      manter mesmo que voc� caia fora, seja abduzido ou passe programar em BASIC, jamais retenha informa��es.
      D� vaz�o para que sua mente consiga produzir mais coisas aqui e em outro lugar

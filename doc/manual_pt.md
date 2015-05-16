# Um *build system* chamado Hefesto

*por Rafael Santiago*

----

**Resumo**: Nesse documento voc� encontra algumas informa��es relacionadas ao projeto. Minhas motiva��es. Detalhes gerais sobre a ``HSL``. Decis�es de projeto. Loucas divaga��es e ideias que podem ferir as suas, se voc� for uma alma sens�vel... :-)

----

## Hefesto quem?!

``Hefesto`` � um *build system* nada ortodoxo prop�cio para gente conservadora odiar... O principal conceito dele � evidenciar tudo o que est� sendo feito em termos de *build* no seu projeto de *software* lhe oferecendo as ferramentas b�sicas para isso.

## A motiva��o

*Hefesto* � um *build system* que resolvi criar buscando responder algumas perguntas que sempre fiz em termos de *build systems*:

- Por que *build systems* adotam linguagens excessivamente declarativas?
- Por que a sintaxe dessas linguagens em geral s�o horrendas?
- Por que o desenvolvedor n�o pode se sentir programando o *build*?
- Por que para que ele se sinta assim precisa empilhar tanta coisa junto?
- � feio, nada polido, prezar por.... concis�o, completude e clareza?!
- Por que adotar a filosofia do caracol para se sentir em casa?

Talvez � medida que come�ar descrever o que criei voc� note que o *Hefesto* n�o � necessariamente um *build system* mas sobre o que um *build system* na ess�ncia �.

### Automate or die!

Eu desenvolvo *software* e gosto de automatizar coisas, qualquer tipo de tarefa repetitiva � uma tortura para mim, pois eu poderia estar fazendo outra coisa no lugar da repeti��o.

Atualizando minha �ltima afirma��o: eu desenvolvo *software* e gosto de pensar em coisas novas o tempo todo e por isso *preciso* automatizar.

Ao meu ver a automatiza��o mais b�sica no ciclo que envolve o desenvolvimento de um *software* remonta aos prim�rdios de seu surgimento, em outras palavras, remonta ao seu *build*.

Temos incont�veis formas de automatizar *builds* desde *shell scripts* e *batch files* arcanas, at� os *Makefiles*, *Jamfiles* e etc.

Ao longo das d�cadas que venho programando j� usei todos os que citei e mais alguns. Pessoalmente, nunca fui atendido por completo por nenhum deles e �s vezes me irritaram muito.

Vou itemizar uns aspectos gerais que me fizeram desistir deles e ++apenas (� penas mesmo) us�-los++ quando o "senso" comum me obriga:

- Linguagens simb�licas;
- Linguagens [Whitespace-Like](http://pt.wikipedia.org/wiki/Whitespace);
- O poder de fogo n�o � constante quando mudamos de plataforma;
- �s vezes � preciso instalar uma infinidade de coisa para manter o poder de fogo, sem necessidade, se o *build system* tivesse sido bem pensado;
- Documenta��o confusa e nada direta;
- Mistureba de Linguagens sem nenhuma necessidade;
- Utiliza��o confusa, envolvendo duas ou mais ferramentas para cumprir todo o ciclo do processo;
- Ferramentas visuais baseadas em *XML* que � por sua vez horr�vel de versionar e tirar *diffs*, a coisa se torna ainda pior quando o *XML* � gerado automaticamente;
- Adaptar seu senso de qualidade e clareza nivelando por baixo, algo como, preciso pensar meu c�rculo assim pois meu *build system* me oferece uma lacuna no formato de um tri�ngulo... "Sim, veja! � incr�vel como meu c�rculo se encaixa nesse tri�ngulo menor que ele!!! Por essa eu n�o esperava...."

## Como funciona o *Hefesto*

O *Hefesto* leva em considera��o que voc� � um programador que ++conhece++ os compiladores que est� usando. Se voc� se julga um *sniper* mas at� hoje se limitou em usar armas de *paintball* pare de ler isso.

Ele � baseado no conceito de automatizar a ess�ncia do processo de *build* de um *software* e isso recai na compila��o e *linkedi��o*, na maioria das vezes. Sou programador *C* e o *Hefesto* � em grande parte feito nela, quando n�o, � feito na Linguagem que ele implementa, que por sinal vou apresentar depois de mostrar a cara de um *script* de *build* *Hefesto*.

Quase todo *build system* possui um arquivo m�gico que se existe no diret�rio *sheebang!* No *Hefesto* n�o... ele deixa voc� dar o nome que melhor se adequa ao
seu estado de coisas. Eu gosto de chamar os meus de ``Forgefiles``.

Segue um exemplo de um ``Forgefile`` para uma *lib* escrita em *C*:

		# Comment-sample: Forgefile.hsl...

        include ~/toolsets/gcc/gcc-lib.hsl

        var sources type list;
        var includes type list;
        var cflags type list;

        project here : toolset "gcc-c-lib" : $sources, $includes, $cflags, "libhere.a";

        here.prologue() {
        	$sources.ls(".*\\.c$");
        }

A ``HSL`` j� come�a aqui e continua dentro do ``toolset``. ``HSL`` pode ser entendida como ``H``efesto ``S``cripting ``L``anguage. � a Linguagem que se usa tanto para criar *builds* ou para automatizar a ess�ncia deles. O conjunto de automatiza��es do ``essencial de um build`` pode ser entendido como um ``toolset``.

Note que no ``Forgefile`` apresentado, ap�s o coment�rio, � feita uma inclus�o bem sugestiva. Estamos incutindo nesse ``Forgefile`` uma base de conhecimento pr�via que recai sobre como executar um *build* de uma biblioteca escrita em *C* usando o compilador *GCC*.

Depois disso, algo que muitos odeiam com paix�o. Voc� precisa declarar tudo, absolutamente tudo o que vai usar. Algo como: "ei pessoal, preciso usar isso aqui ent�o, com licen�a viu?".

Do ponto de vista do *design de Linguagens de programa��o*, eu pessoalmente acho que a necessidade de declara��o de uma vari�vel � uma *feature* que salta do dispositivo direto para a consci�ncia do usu�rio, pois no momento da declara��o ele ser� levado a pensar sobre o porqu� e se realmente precisa daquela vari�vel naquele dado momento.
Salvo isso, continuemos...

Essas vari�veis declaradas s�o utilizadas pela ``fun��o de forja`` (entenda por enquanto como o ponto de entrada para a parte mais interna do *build*).

Ap�s a declara��o das vari�veis, ``declaramos o projeto``. Dizendo algo na linha: 

>"Esse projeto se chama "here" � uma *lib* escrita em *C* que esperamos compilar com o *GCC*. Seguem os par�metros na ordem que o motor de *build* para esse tipo de coisa espera."

Esse ``toolset`` espera receber uma lista de ``c�digos`` para compilar, uma lista de diret�rios de ``includes`` usados durante a compila��o, uma lista de ``op��es de compila��o`` que o compilador em quest�o entende e um ``nome para o arquivo`` que ser� produzido pelo processo, em outras palavras a *lib* propriamente dita.

Um problema com a maioria dos *build systems* � quanto a defini��o dos c�digos a serem processados. Alguns deixam a coisa solta e podemos ler essa lista de qualquer lugar, outros n�o disponibilizam mecanismos para isso.

O *Hefesto* fica no meio termo, antes de um *build* come�ar, �s vezes, para n�o dizer quase sempre... existem uma infinidade de coisas muito espec�ficas �quele projeto que precisam ser feitas. Quando um projeto � criado no *Hefesto*, juntamente com ele s�o criados tr�s pontos de entrada: ``preloading``, ``prologue`` e ``epilogue``.

Confira na **Tabela 1** em que momento do processo esses pontos de entrada s�o atingidos. A ideia b�sica aqui �: se existe c�digo definido dentro deles, no momento esperado, esses c�digos ser�o executados.

**Tabela 1**: Os est�gios de um projeto *Hefesto*.

| **Project entry-point** |            **Executado**         |
|:-----------------------:|:--------------------------------:|
|     ``preloading``      | Antes mesmo de carregar o toolset|
|     ``prologue``        | Antes da forja ser iniciada      |
|     ``epilogue``        | Ap�s a forja ser finalizada      |

Esque�amos por hora o ``preloading`` e o ``epilogue``. H� uma coisa muito b�sica que sempre dever� ser feita antes de come�ar uma forja que � coletar os *file paths* dos c�digos que precisam ser processados. Ent�o, no ``prologue`` do exemplo:

		here.prologue() {
        	$sources.ls(".*\\.c$");
        }

N�o se preocupe com o ``.ls()``... Nas se��es futuras quando descrever melhor a ``HSL`` os facilitadores de lista ser�o apresentados e tudo talvez fa�a mais sentido.

Com o ``Forgefile`` escrito, a forja poderia ser invocada na linha de comando da seguinte forma:

> ``hefesto --forgefiles=Forgefile.hsl --Forgefile-projects=here``

Note que na op��o ``--forgefiles`` s�o especificados uma lista de arquivos contendo projetos. A outra op��o � din�mica e baseada nos arquivos passados em ``--forgefiles``. O esquema geral dessa op��o din�mica �:

> ``--<file-name>-projects=<projects defined inside this file>``

J� sei:

> ZzZZzzzZzzzZzZZZZZZzzzzzzZzzzZzzzzzZZZZZZZzzzzZZZ que comando longo... n�o posso digitar algo mais breve? 

Pode sim, voc� precisa criar um arquivo de invoca��o e imolar 5 cabras em nome de *Hefesto*... O arquivo de invoca��o precisa estar no diret�rio onde voc� deseja invocar a forja, o nome desse arquivo � ``.ivk`` e dentro dele voc� deve colocar a linha de comando exatamente como passaria para o *Hefesto*.

Com o ``.ivk`` configurado, estando no diret�rio dele, apenas digitando ``hefesto`` voc� ter� a forja nos moldes padr�o que voc� necessita e definiu, caso passe op��es nessa chamada, as op��es que voc� fornecer ter�o preced�ncia maior quando *mergeadas* com as op��es do arquivo de invoca��o.

E quanto as cabras?! N�o precisa, era s� brincadeira...

Pronto, agora voc� j� sabe os passos b�sicos para compor um ``Forgefile`` no *Hefesto*, mas o que voc� n�o sabe ainda s�o os detalhes gerais da ``HSL`` e de como criar mais ``toolsets`` que atendam suas necessidades.

Os ``toolsets`` por sua vez s�o por��es de c�digo ``HSL`` que podem ter suas pr�prias conven��es, conveni�ncias, etc. Por isso, antes de us�-los uma boa provid�ncia � consultar a documenta��o espec�fica desse ``toolset``. Se voc� o baixou da base oficial provavelmente encontrar� algum texto que o detalhe.

### Reprocessando somente o que mudou desde a �ltima forja, tem como?

Sim, isso envolve requisitar essa necessidade na declara��o do projeto. Vamos usar o mesmo projeto de *lib* do exemplo anterior.

Anteriormente a declara��o era essa:

		project here : toolset "gcc-c-lib" : $sources, $includes, $cflags, "libhere.a";

Agora vamos incluir a especifica��o da cadeia de depend�ncias ou ``dep-chain``. Uma ``dep-chain`` basicamente � uma ``string`` expressa num formato especial:

>``<file-path>`` **:**  ``<file-path_0>`` [ **&** ``<file-path_n>`` ] **;**

Imagine que ``a.x`` depende de ``b.x`` que depende de ``c.x`` que por sua vez depende de ``d.x`` e ``e.x``. A ``dep-chain`` para essa situa��o seria:

>a.x: b.x;
>
>b.x: c.x;
>
>c.x: d.x & e.x;

No caso de programas reais isso pode ser bem ma�ante de se escrever, a biblioteca padr�o do ``Hefesto`` inclui fun��es em ``HSL`` que tentam inferir por meios heur�sticos a interdepend�ncia entre os arquivos que comp�em um projeto.

Segue um uso pr�tico das ``dep-chains``:

		include ~/toolsets/gcc/gcc-lib.hsl
		include ~/toolsets/common/utils/lang/c/dependency_scanner.hsl

		var deps type string;
		var sources type list;
		var includes type list;
		var cflags type list;
		var libraries type list;
		var ldflags type list;

		project here : toolset "gcc-c-lib" : dependencies $deps : $sources,
        		                                                  $includes,
                		                                          $cflags,
                        		                                  "libhere.a" ;

		here.prologue() {
    		$deps = get_c_cpp_deps();
    		$sources.ls(".*\\.c$");
		}

Note que agora foi inclusa a diretiva ``dependencies <string>`` na declara��o do projeto, al�m do uso da fun��o ``get_c_cpp_deps()`` importada de ``dependency_scanner.hsl``. Contudo, voc� mesmo poderia grafar a sua ``string`` de depend�ncia, caso quisesse. Importante ressaltar que uma ``dep-chain`` mal formada � silenciosamente descartada pelo aplicativo. Esteja sempre atento durante a composi��o delas.

E Pronto! Apenas com isso seus arquivos come�ar�o serem processados somente quando houverem altera��es expl�citas neles ou em algum outro arquivo que eles dependam.

#### Como for�ar o reprocessamento de tudo?

Use a op��o ``--forge-anyway`` ao invocar uma forja.

#### Algo mais que deva saber sobre as *dep-chains*?

Sim, quando voc� adota o uso de ``dep-chains`` em um projeto os seus argumentos durante a invoca��o da forja come�am ser monitorados. A decis�o de projeto que adotei foi:

>Se existe um ``bit`` que seja de diferen�a entre os argumentos de forja atuais e os �ltimos de uma forja bem sucedida, **tudo ser� reprocessado**. Ao meu ver o pre�o que se paga � menor. Se n�o h� como saber que ``flag`` � pass�vel de reprocessamento de um mar de ``flags`` � mais confi�vel sempre reprocessar e acabou. A praticidade cotidiana n�o � uma *top-model* mas na sua simplicidade traz seus encantos...

>Sinceramente eu n�o acho que programadores realmente ocupados e com objetivos reais e bem conscientes ficam macaqueando ``flags`` aleat�rias o tempo todo para um ``build`` ou disputando ``build-turfe`` por a�. Voc� conhece algum?!

Uma altera��o de arquivo � julgada **n�o pela data de altera��o**, mas **com base no conte�do**. Com um ``bit`` de diferen�a um arquivo j� ser� considerado "sujo".

### Yoda`s proposal: que tal em *runtime* o *toolset* mudar?

Sim meu jovem *Luke*, n�o tenha medo muito... isso � poss�vel. Para isso s� � preciso ter uma precau��o *Jedi*: os *toolsets* a serem escolhidos devem possuir a mesma assinatura de fun��o para a fun��o de forja, em outras palavras, devem receber o mesmo n�mero de argumentos, na mesma ordem e tipo.

Lembra quando foram apresentados os ``entry-points`` de um projeto de forja? Que o ``entry-point`` chamado ``preloading`` ocorre mesmo antes do ``toolset`` ao qual o projeto � dependente ser carregado? Vamos usar esse ``big-bang`` para criar um *Forgefile* mais adapt�vel ao ambiente.

Vamos pegar o projeto daquela *lib* apresentado e criar o seguinte requisito:

>Se estivermos no ``Windows`` daremos prefer�ncia por usar o *Visual Studio 2012*, caso ele exista na m�quina. N�o existindo usaremos o *GCC*, nas demais plataformas usaremos sempre o *GCC*.

Vou apresentar o *Forgefile* alterado e comentar as partes interessantes depois.

		include ~/toolsets/gcc/gcc-lib.hsl
		include ~/toolsets/vc/vc110-lib.hsl
		include ~/toolsets/common/utils/lang/c/dependency_scanner.hsl

		var deps type string;
		var sources type list;
		var includes type list;
		var cflags type list;
		var libraries type list;
		var ldflags type list;
		var current_toolset type string;

		project here : toolset $current_toolset : dependencies $deps : $sources,
        			                                                   $includes,
                    			                                       $cflags,
                                			                           "libhere.a" ;

		function has_vs_110() : result type int {
            var winreg_rkey type list;
            $winreg_rkey.add_item("HKLM");
            $winreg_rkey.add_item("HKCU");

            var subkeys type list;
            $subkeys.add_item("\\SOFTWARE\\Microsoft\\VisualStudio\\SxS\\VS7\\11.0");
            $subkeys.add_item("\\SOFTWARE\\Wow6432Node\\Microsoft\\VisualStudio\\SxS\\VS7\\11.0");

			var s type int;
            var subkey type string;
            var w type int;
            var root_key type string;
            var install_dir type string;

            $s = 0;
            while ($s < $subkeys.count()) {
            	$subkey = $subkeys.item($s);
            	$w = 0;
            	while ($w < $winreg_rkey.count()) {
                	$root_key = $winreg_rkey.item($w);
        			$install_dir = hefesto.sys.env("WINREG:" +
            				                       $root_key +
                                                   $subkey);
                    if ($install_dir.len() > 0) result 1;
                    $w = $w + 1;
        		}
                $s = $s + 1;
           }
           result 0;
        }

        here.preloading() {
        	$current_toolset = "gcc-c-lib";
        	if (hefesto.sys.os_name() == "windows") {
            	if (has_vs_110()) {
                	$current_toolset = "vc110-lib";
                }
            }
        }

		here.prologue() {
    		$deps = get_c_cpp_deps();
    		$sources.ls(".*\\.c$");
		}

A fun��o ``has_vs_110`` verifica no registro do sistema a entrada de chave existente caso haja o *Visual Studio* na m�quina, leia a se��o ``Sobre a HSL`` que voc� entender� a l�gica b�sica e o uso de ``hefesto syscalls`` nessa fun��o. Se existir na m�quina retornar� 1, de outra forma 0.

Note que no ``preloading`` do projeto apenas chamaremos essa fun��o se estivermos executando a forja sob o ``Windows`` (novamente, consulte a se��o ``Sobre a HSL``) e se existir o *Visual Studio* na m�quina, setamos o nome do toolset para "vc110-lib". Caso contr�rio, o ``toolset`` ser� o padr�o "gcc-c-lib". Pelo fato da declara��o possuir uma indire��o para o nome do ``toolset`` via a vari�vel que setamos no ``preloading``:

		project here : toolset $current_toolset : dependencies $deps : $sources,
        			                                                   $includes,
                    			                                       $cflags,
                                			                           "libhere.a" ;

Passamos ter a sele��o do ``toolset`` em ``runtime``, pois quando o ``toolset`` estiver sendo carregado o ``Hefesto`` j� vai ter passado pelo ``preloading`` do nosso projeto. Por esse motivo � importante ter a mesma assinatura de forja entre os ``toolsets``, pois s� podemos declarar um projeto uma vez. Mas isso vai da intelig�ncia e mais do que isso, do senso de reutiliza��o do desenvolvedor dos ``toolsets`` que voc� for usar.

Mas ainda tem um "problema" nisso a�... observe no in�cio do exemplo:

		include ~/toolsets/gcc/gcc-lib.hsl
		include ~/toolsets/vc/vc110-lib.hsl

Nossa forja � multiplataforma, mas n�o precisamos incluir o m�dulo ``vc110-lib.hsl`` fora do ``Windows``, n�o usaremos *Visual Studio* no ``Linux``, para que ocupar o ``Hefesto`` em processar esse m�dulo sem necessidade toda vez? Que tal melhorar para:

		include ~/toolsets/gcc/gcc-lib.hsl
		include on windows ~/toolsets/vc/vc110-lib.hsl

Pronto!

A diretiva ``include`` aceita uma lista de plataformas para efetivamente incluir um arquivo ``HSL`` dentro de outro, se houvesse necessidade de incluir um arquivo apenas no ``FreeBSD`` e no ``Linux``:

		include on freebsd,linux posix/utils.hsl

### Como rodo meus testes?

Nada me irrita mais do que a necessidade de criar ``batch-files`` ou mesmo ``shell-scripts`` para rodar testes e outras tarefas pr� e p�s compila��o. Organiza��o ao meu ver envolve uniformidade e quanto menos mistureba melhor e o para�so seria perfeito se pudessemos deixar tudo dentro da mesma esfera.

Que tal usar o ``entry-point epilogue`` para disparar a compila��o e execu��o dos testes, avaliando se quebraram ou passaram? No exemplo, da nossa *lib*, adicionar�amos:

		here.epilogue() {
    		var notest type list;
    		if (hefesto.sys.last_forge_result() == 0) {
        		$notest = hefesto.sys.get_option("no-test");
        		if ($notest.count() == 0) {
            		run_tests();
        		}
    		}
		}

		function run_tests() : result type none {
    		var retval type int;
    		hefesto.sys.cd("test");
    		$retval = hefesto.sys.forge("here-test", "Forgefile.hsl", "--bin-output-dir=bin --obj-output-dir=obj");
    		hefesto.sys.cd("..");
		}

Desculpe se estou adiantando um pouco as coisas aqui, mas basicamente em ``epilogue`` verifico se o ``build`` atual de nossa *lib* foi realmente bem sucedido, se tiver sido, vejo se a op��o de usu�rio ``--no-test`` foi passada, caso n�o tenha sido, chamo a fun��o de execu��o dos testes.

A fun��o ``run-tests`` por sua vez muda para o subdiret�rio ``test`` onde teremos um outro projeto de forja o qual disparamos. Ap�s isso, finalizamos voltando ao diret�rio anterior.

Agora vamos ver como � esse *Forgefile* dos testes:

		include ~/toolsets/gcc/gcc-app.hsl

		var sources type list;
		var includes type list;
		var libraries type list;
		var ldflags type list;
		var cflags type list;

		project here-test : toolset "gcc-c-app" : $sources, $includes, $cflags,
        		                        $libraries, $ldflags, "here_unittest" ;


		here-test.prologue() {
    		$sources.ls(".*\\.c$");
    		$ldflags = hefesto.sys.get_option("ldflags");
    		$ldflags.add_item("../lib/libhere.a");
    		$includes = hefesto.sys.get_option("includes");
    		$includes = hefesto.sys.get_option("libraries");
    		$includes = hefesto.sys.get_option("cflags");
		}

		function run_unittests() : result type int {
    		var retval type int;
    		if (hefesto.sys.os_name() != "windows") {
        		$retval = hefesto.sys.run("bin/here_unittest");
    		} else {
        		$retval = hefesto.sys.run("bin\\here_unittest.exe");
    		}
    		result $retval;
		}

		here-test.epilogue() {
    		if (hefesto.sys.last_forge_result() == 0) {
        		if (run_unittests() != 0) hefesto.sys.exit(1);
    		}
		}

A fun��o mais importante � a ``run_unittests`` chamada � partir do ``epilogue`` caso retorne algo diferente de zero sai com c�digo 1, o que far� o *build* quebrar.

Eu posso dizer que encontrei meu para�so no ``Hades``... :) Espero que voc� continue motivado(a) e siga com a se��o que te ensina de fato programar na ``HSL`` e possa tirar proveito do suporte e liberdade que esse aplicativo procura promover.

## Sobre a HSL

N�o era a minha inten��o inicial criar uma [DSL](http://en.wikipedia.org/wiki/Domain-specific_language) para o *Hefesto*, o fato � que cheguei a conclus�o disso durante o processo de matura��o da ideia. Visto que desejava resolver meus problemas de uma forma mais geral.

Em resumo, tive mais trabalho, contudo, hoje consigo expressar uma boa quantidade de automatiza��es para diversos processos que v�o al�m de simplesmente fazer *builds* de projetos *C/C++*.

### Por que uma *dsl* e n�o *scriptar* uma que j� existe?

Ao meu ver, o problema de usar uma linguagem de uso geral � fazer o usu�rio do *software* se preocupar com conven��es gerais que em suma n�o s�o importantes para expressar suas necessidades. Fora que isso cria uma depend�ncia externa o que te faz ser ref�m das decis�es futuras de um outro projeto. Linguagens de uso geral abrem margem para muitas possibilidades, muitas possibilidades abrem margem para desordem.

### Definindo as bases

A ``HSL`` em momento nenhum esquece que � uma linguagem feita em suma para automatizar coisas, n�o comece querer programar *software* de uso geral com ela. ++Por favor n�o...++

Ela possui 4 tipos primitivos e n�o existe uma conveni�ncia para se utilizar *user-defined types*, a **Tabela 2** sumariza esses tipos.


**Tabela 2**: Tipos primitivos presentes na ``HSL``.

| **Palavra reservada** |                 **Tipo**                          |
|:---------------------:|:-------------------------------------------------:|
|     ``int``           | Inteiro de 32/64 bits                             |
|   ``string``          | Sequ�ncia de caracteres                           |
|    ``file``           | Um descritor de arquivo                           |
|    ``list``           | Container para dados do tipo ``int`` ou ``string``|

Fato: vari�veis precisam ser declaradas.

Em qualquer ponto de um c�digo ``HSL`` voc� pode declarar uma vari�vel sob o seguinte esquema:

> **var** ``<var-name>`` **type** ``<type-name>`` **;**

Saiba que ``<var-name>`` pode ser composto por ``[A-Za-z0-9_]``. Pode-se ter uma e somente uma declara��o por linha.

Exemplos pr�ticos:

		var my_name type string;
		var my_age type int ;
		var my_sloopy_list_decl
		type
		list;

Para acessar uma vari�vel declarada (me desculpe o pleonasmo) preceda-a com o s�mbolo ``$``, assim:

		$my_name = "John doe.";
		$my_age = -1;

``Branches`` condicionais podem ser expressos da seguinte forma:

> **if** **(** ``<expr>`` **)** **{** ``<hsl-stmt>`` **}** [ **else** **{** ``<hsl-stmt>`` **}** ]

ou

> **if** **(** ``<expr>`` **)** ``<hsl-single-stmt>`` [ **else** ``<hsl-single-stmt>`` ]

S� existe uma forma de expressar ``loops`` na Linguagem que � via ``while``, segue o formato dele:

> **while** **(** ``<expr>`` **)** **{** ``<hsl-stmt>`` **}**

ou

> **while** **(** ``<expr>`` **)** ``<hsl-single-stmt>``

A **Tabela 3** re�ne os operadores dispon�veis para compor express�es na ``HSL``.

**Tabela 3**: Operadores dispon�veis at� o momento.

|   **Operador**   |     **Opera��o**   | **Tipo** |
|:----------------:|:------------------:|:--------:|
|     ``==``       |      Igual a       |  L�gico  |
|     ``!=``       |   Diferente de     |  L�gico  |
|      ``<``       |     Menor que      |  L�gico  |
|      ``>``       |     Maior que      |  L�gico  |
|     ``>=``       | Maior ou igual que |  L�gico  |
|     ``<=``       | Menor ou igual a   |  L�gico  |
|     ``&&``       |      .E.           |  L�gico  |
|   &#124;&#124;   |      .OU.          |  L�gico  |
|     ``&``        |      .E.           |  Bitwise |
|     &#124;       |      .OU.          |  Bitwise |
|     ``<<``       |    ``Left Shift``  |  Bitwise |
|     ``>>``       |    ``Right Shift`` |  Bitwise |


Fun��es podem retornar qualquer tipo primitivo ou nada. O esquema geral de declara��o �:

>**function** ``<function-name>`` **(** ``<var-decl-list>`` **)** **: result type ** **{** ``<hsl-stmt>`` **}**

Os caracteres aceitos para ``nomenclatura de uma fun��o`` **s�o os mesmos** aceitos para ``nomenclatura de vari�veis``.

Um exemplo mais pr�tico... Uma fun��o que calcula de forma recurssiva o fatorial de um n�mero fornecido:

		function fatorial(n type int) : result type int {
			if ($n == 0) return 1;
        	return fatorial($n - 1) * $n;
    	}

Uma fun��o que n�o retorna nada, cujo ``return type`` deve ser ``none``:

		function say_hello() : result type none
        {
        	hefesto.sys.echo("Hello, creative mind....\n")
        }

### As *Hefesto Syscalls*

Certo, o �ltimo exemplo com uma fun��o in�til que s� dizia al�, n�o foi t�o in�til... Serviu para te criar uma d�vida:

>"O que afinal de contas � esse neg�cio de ``hefesto.sys.whatever``??"

Nada � por acaso nessa vida, acredite! Uma *[abomin�vel](http://en.wikipedia.org/wiki/Eastern_mole#/media/File:ScalopusAquaticus.jpg) [doninha](https://what-if.xkcd.com/4/) documentadora* p�s aquilo l� para fazer voc� trope�ar e cair aqui.... Quando comecei pensar a ``HSL`` uma das minhas principais indaga��es eram sobre o que � comum a quase todo processo de *build* e dessas coisas comuns, o que � direta ou indiretamente requisitado ao ``Sistema Operacional`` em quest�o.

Essas indaga��es me levaram criar uma camada de abstra��o que garante escrever passos comuns em uma *build-task* mas heterog�nos em termos pr�ticos de um ``OS`` para outro, apenas uma vez e ter a garantia que rodar�o iguais em qualquer plataforma suportada pelo ``Hefesto``.

Essa camada de abstra��o pode ser acessada � partir do ``subsistema sys`` do ``Hefesto``, da seguinte forma:

>``hefesto.sys.<sys-call>(<arg-list>)``

Esse ``subsistema`` � chamado de ``syscalls``, mas aqui n�o se deixe levar pelo conceito cl�ssico de *syscall*. De fato, voc� encontrar� muito mais do que *"syscalls"*. Encontrar� coisas que fazem muito mais numa �nica chamada e num n�vel bem mais alto do que as boas e velhas *syscalls* do nosso bom e velho *Unix*, por exemplo.

Escolhi esse nome, porque durante meu trabalho notei que a maioria dos pontos de n�o portabilidade de uma *build-task* recaiam na maior parte sobre algumas *syscalls* verdadeiras. Ent�o, fica aqui explicada a origem de qualquer futuro equ�voco.

Uma outra forma de aceitar a n�o ortodoxia das ``hefesto syscalls`` pode ser entendendo que elas tamb�m englobam opera��es comuns de serem requisitadas e por isso postas de forma ``built-in`` no *build-system*. Criando o que eu aqui gosto de chamar de ``subsistema``.

Na **Tabela 4** segue uma listagem com uma r�pida descri��o do que uma referida ``syscall`` faz.

**Tabela 4**: ``Hefesto  syscalls`` dispon�veis at� o presente momento.

|          **Syscall**            |         **Utilitade**                                                                                         |
|:-------------------------------:|--------------------------------------------------------------------------------------------------------------:|
| ``replace_in_file()``           |substitui um texto encontrado via uma express�o regular                                                        |
| ``lines_from_file()``	          |filtra linhas que casam com a express�o regular passada                                                        |
| ``ls()``	                      |retorna a contagem de arquivos encontrados no diret�rio corrente que casam seus nomes com a regex fornecida    |
| ``pwd()``	                      |retorna o fullpath do diret�rio corrente                                                                       |
| ``cd()``	                      |muda o diret�rio corrente para o caminho passado                                                               |
| ``rm()``	                      |remove o filepath fornecido                                                                                    |
| ``cp()``	                      |copia um arquivo/diret�rio de um path existente para outro                                                     |
| ``mkdir()``	                  |cria um diret�rio                                                                                              |
| ``rmdir()``	                  |remove um diret�rio vazio                                                                                      |
| ``fopen()``	                  |abre um arquivo retornando seu descritor que deve ser atribu�do a uma vari�vel do tipo file                    |
| ``fwrite()``	                  |escreve dados para o arquivo referenciado pelo descritor de arquivo fornecido                                  |
| ``fread()``	                  |l� dados do arquivo referenciado pelo descritor de arquivo fornecido                                           |
| ``fclose()``	                  |limpa todos os recursos alocados por um descritor de arquivo                                                   |
| ``feof()``	                  |verifica se � o final do arquivo                                                                               |
| ``fseek()``	                  |pula para um determinado offset do arquivo                                                                     |
| ``fseek_to_begin()``	          |pula para o in�cio do arquivo                                                                                  |
| ``fseek_to_end()``	          |pula para o final do arquivo                                                                                   |
| ``fsize()``	                  |retorna o tamanho do arquivo em bytes                                                                          |
| ``ftell()``	                  |retorna o offset corrente do arquivo                                                                           |
| ``run()``	                      |roda um processo externo, retornando seu exit code                                                             |
| ``echo()``	                  |escreve texto na tela                                                                                          |
| ``env()``	                      |retorna o conte�do de uma vari�vel de ambiente                                                                 |
| ``prompt()``	                  |l� dados do teclado, esperando a confirma��o via "ENTER"                                                       |
| ``exit()``	                  |aborta a m�quina virtual do hefesto, alterando o error level para o valor fornecido                            |
| ``os_name()``	                  |retorna o nome da plataforma corrente                                                                          |
| ``get_option()``	              |retorna dados de uma op��o fornecida via linha de comando                                                      |
| ``make_path()``	              |cria uma string que corresponde a um caminho no sistema de arquivos                                            |
| ``last_forge_result()``	      |obt�m o exit code do �ltimo processo de forja executado                                                        |
| ``forge()``	                  |invoca um outro projeto de forja                                                                               |
| ``byref()``	                  |atualiza os valores de um argumento de fun��o para a vari�vel externa que foi passada como esse argumento local|
| ``time()``	                  |retorna uma string representando o tempo do sistema de acordo com o formato passado                            |
| ``setenv()``	                  |cria uma vari�vel de ambiente                                                                                  |
| ``unsetenv()``	              |remove uma vari�vel de ambiente                                                                                |
| ``call_from_module()``	      |chama uma fun��o implementada em uma biblioteca din�mica                                                       |
| ``get_func_addr()``	          |obt�m o endere�o de um nome de fun��o passado                                                                  |
| ``call_func_addr()``	          |tenta fazer uma chamada de fun��o � partir do endere�o passado                                                 |

#### Um guia pr�tico para cada *Hefesto syscall*

Aqui nessa parte voc� pode explorar melhor como usar cada ``syscall``, vendo que argumentos recebem e o que retornam. Tudo isso de um modo mais pr�tico.

##### ++replace_in_file()++

Substitui dados em um arquivo. O primeiro argumento deve ser o ``file path``, o segundo � o padr�o de busca expresso por uma ``regex``, o terceiro � o texto de substitui��o desejado.

		function replace_in_file_sample() : result type none {
 			hefesto.sys.replace_in_file("test.txt", "^foo.*", "all initial foo to bar");
		}
##### ++lines_from_file()++

Filtra linhas de um arquivo. O primeiro argumento deve ser o ``file path``, o segundo � o padr�o de busca expresso por uma ``regex``. A ``syscall`` retorna uma lista contendo as linhas filtradas do arquivo.

		function lines_from_file_sample() : result type none {
 			var retval type list;
 			$retval = hefesto.sys.lines_from_file("test.txt", "^foo.*");
		}

##### ++ls()++

Lista arquivos no diret�rio corrente. Recebe somente um argumento que deve ser o padr�o de listagem em ``regex``.

		function ls_sample() : result type none {
 			if (hefesto.sys.ls(".*(c|cpp|s|asm)$") > 0) {
  				hefesto.sys.echo("Hey Beavis, Huh cool files to delete here!! Yeah yeah! Butt-head remove them! remove them!\n");
 			} else {
  				hefesto.sys.echo("ohh, nothing to screw up here.\n");
 			}
		}

##### ++pwd()++

Retorna o diret�rio corrente. � muito ``DIF�CIL`` de usar essa fun��o ``built-in``, d� uma olhada:

		function pwd_only_to_PHDs() : result type none {
 			hefesto.sys.echo("The current work directory is: " + hefesto.sys.pwd() + "\n");
		}

##### ++cd()++

Muda o ``cwd`` para o diret�rio fornecido via argumento.

		function cd_sample() : result type none {
 			hefesto.sys.cd("/home/rs");
		}

##### ++rm()++

Remove um arquivo.

		function rm_sample() : result type none {
 			hefesto.sys.rm("some.lint~");
		}

##### ++cp()++

Copia arquivo/diret�rios para o diret�rio especificado. O primeiro argumento � o padr�o regex correspondente ao source, o segundo � o destino.

		function cp_sample() : result type none {
 			hefesto.sys.cp(".*.(exe|dll|msi)", "wpkg");
		}

##### ++mkdir()++

Cria o diret�rio sob o diret�rio de trabalho.

		function mkdir_sample() : result type none {
 			hefesto.sys.mkdir("wpkg");
		}

##### ++rmdir()++

Remove um diret�rio vazio.

		function rmdir_sample() : result type none {
 			hefesto.sys.rmdir("stage");
		}


##### ++fopen()++

Abre um arquivo retornando o descritor que pode ser manipulado. O primeiro argumento � o ``file path``, o segundo � o modo de abertura. Os modos seguem o ``fopen`` cl�ssico da ``libc`` ("r" = somente leitura, "w" = somente escrita, "a" = modo ``append``).

		function fopen_sample() : result type none {
 			var fp type file;
 			$fp = hefesto.sys.fopen("test.dat", "a");
		}


##### ++fwrite()++

Escreve dados em um descritor de arquivo aberto com modo de escrita ou ``append``. O primeiro argumento � o ``buffer`` de dados, o segundo � o quanto escrever desse ``buffer``, o terceiro � o descritor de arquivo.

Retorna a quantidade de dados escritos no arquivo.

		function fwrite_sample() : result type none {
 			var fp type file;
 			$fp = hefesto.sys.fopen("test.dat", "a");
 			var buf type string;
 			$buf = "that's all folks for fwrite!\n";
 			hefesto.sys.fwrite($buf, $buf.len(), $fp);
		}

##### ++fread()++

L� dados de um descritor de arquivo (�bvio: aberto em modo de leitura) avan�ando o ponteiro de arquivo por *n* ``bytes`` lidos. O primeiro argumento � o ``buffer`` de dados, o segundo � a quantidade que deve ser lida � partir do arquivo, o terceiro � o descritor.

Retorna a quantidade de dados lidos do arquivo.

		function fread_sample() : result type none {
 			var fp type file;
 			$fp = hefesto.sys.fopen("test.dat", "r");
 			var byte type string
 			hefesto.sys.fread($byte, 1, $fp);
		}


##### ++fclose()++

Fecha/limpa os recursos internos associados ao descritor de arquivo. Recebe o descritor que deve ser fechado. � importante sempre chamar esta fun��o depois de uma manipula��o de arquivo. Seja higi�ncio(a)!

		function fclose_sample() : result type none {
 			var fp type file;
 			$fp = hefesto.sys.fopen("test.dat", "w");
 			# TODO: do some manipulation here...
 			hefesto.sys.fclose($fp);
		}

##### ++feof()++

Retorna *1* se o final do arquivo foi alcan�ado de outra forma *0*. Recebe o descritor de arquivo que deve ser verificado.

		function feof_sample() : result type none {
 			var fp type file;
 			$fp = hefesto.sys.fopen("test.dat", "r");
 			if (hefesto.sys.feof($fp) == 1) {
  				hefesto.sys.echo("file end.\n");
			} else hefesto.sys.echo("NOT file end.\n");
 				hefesto.sys.fclose($fp);
			}
        }

##### ++fseek()++

Pula para um ``offset`` espec�fico do arquivo do in�cio ao fim. O primeiro argumento � o descritor de arquivo, o segundo � o ``offset`` desejado.

		function fseek_sample() : result type none {
 			var fp type file;
 			$fp = hefesto.sys.fopen("test.dat", "r");
 			hefesto.sys.fseek($fp, 10);
 			hefesto.sys.fclose($fp);
		}

##### ++fseek_to_begin()++

Pula para o in�cio do arquivo. Recebe o descritor associado como argumento.

		function fseek_to_begin_sample() : result type none {
 			var fp type file;
 			$fp = hefesto.sys.fopen("test.dat", "r");
 			hefesto.sys.fseek_to_begin($fp); # yes this is a very useless dummy sample...
 			hefesto.sys.fclose($fp);
		}

##### ++fseek_to_end()++

Pula para o final do arquivo. Recebe o descritor associado como argumento.

		function fseek_to_end_sample() : result type none {
 			var fp type file;
 			$fp = hefesto.sys.fopen("test.dat", "r");
 			hefesto.sys.fseek_to_end($fp);
 			hefesto.sys.fclose($fp);
		}

##### ++fsize()++

Retorna os ``bytes`` totais de um arquivo associado ao descritor de arquivo passado.

		function fsize_sample() : result type none {
 			var fp type file;
 			$fp = hefesto.sys.fopen("test.dat", "r");
 			hefesto.sys.echo("The has " + hefesto.sys.fsize($fp) + "byte(s).\n");
 			hefesto.sys.fclose($fp);
		}

##### ++ftell()++

Retorna o ``offset`` corrente do descritor de arquivo.

		function ftell_sample() : result type none {
 			var fp type file;
 			$fp = hefesto.sys.fopen("test.dat", "r");
 			hefesto.sys.echo("The current offset should be 0 and is " + hefesto.sys.ftell($fp) + ".\n");
 			hefesto.sys.fclose($fp);
		}

##### ++run()++

Roda um processo externo retornando o ``exit code``. A chamada ``run`` � sempre bloqueante.

		function sync_run_sample() : result type none {
 			hefesto.sys.echo("ls /dev exits with " + hefesto.sys.run("ls /dev") + " exit code.\n");
		}

Voc� pode tamb�m rodar *n* processos se voc� passar para essa ``syscall`` uma lista contendo as linhas de execu��o. O n�mero de processos concorrentes � controlado pela op��o de linha de comando ``--qsize=n``. Nesse modo, a ``syscall run`` retorna a soma dos ``exit codes``.

		function async_run_sample() : result type none {
 			var wqueue type list;
 			$wqueue.add_item("ls /dev");
 			$wqueue.add_item("ls /home/rs");
 			$wqueue.add_item("echo \"duh!\"");
 			hefesto.sys.echo("The work queue exit code is " + hefesto.sys.run($wqueue) + ".\n");
		}

##### ++echo()++

Exibe uma ``string`` na tela. De fato � uma ``Hefesto syscall`` muito complicada.

		function echo_sample() : result type none {
 			hefesto.sys.echo("Hello world.\n");
		}

##### ++env()++

Obt�m o conte�do de uma vari�vel de ambiente.

		function env_sample() : result type none {
 			hefesto.sys.echo("The current content of Windows PATH variable is = \"" + hefesto.sys.env("PATH") + "\"\n");
		}

##### ++prompt()++

L� um valor do teclado. Retornando os dados lidos.

		function prompt_sample() : result type none {
 			var usr_data type string;
 			$usr_data = hefesto.sys.prompt("Type about an idea and then press enter to confirm this: \n");
 			hefesto.sys.echo("Hey I had an idea: " + $usr_data + "\nWhat do you think?");
		}

##### ++exit()++

Aborta a execu��o da ``HVM`` saindo com o c�digo passado.

		function exit_sample() : result type none {
 			hefesto.sys.exit(1);
		}

##### ++os_name()++

Retorna o nome do sistema operacional onde seu ``HSL`` est� correndo. O retorno � sempre o nome em ``lower-case`` e sem qualquer informa��o de vers�o.

		function env_sample() : result type none {
 			if (hefesto.sys.os_name() == "windows") {
  				hefesto.sys.echo("The current content of Windows PATH variable is = \"" + hefesto.sys.env("PATH") + "\"\n");
 			}
		}

##### ++get_option()++

Obt�m um argumento da linha de comando. Retorna uma lista contendo um ou mais valores ou uma lista vazia.

		function get_option_sample() : result type none {
 			var cups_of_tea type list;
 			$cups_of_tea = hefesto.sys.get_option("cups-of-tea");
 			if ($cups_of_tea.size() == 0)
  				hefesto.sys.echo("--cups-of-tea option not supplied.\n");
 			else
  				hefesto.sys.echo("--cups-of-tea option supplied.\n");
		}

##### ++make_path()++

Cria uma ``string path``. O primeiro argumento � o ``root path``, o segundo � o *"addendum"* do ``path``. Retorna a combina��o correta.

		function make_path_sample() : result type none {
 			hefesto.sys.echo("STRING PATH must be /home/rs \"" + hefesto.sys.make_path("/home", "/rs") + "\"\n.");
		}

##### ++last_forge_result()++

Obt�m o �ltimo resultado de forja (este resultado pode ser alterado pela ``syscall exit``).

		function last_forge_result_sample() : result type none {
 			hefesto.sys.echo("The last forge result was " + hefesto.sys.last_forge_result() + ".\n");
		}

##### ++forge()++

Invoca um projeto de forja. O primeiro argumento � o nome do projeto contido no ``HSL`` informado via primeiro argumento. O terceiro argumento s�o as op��es de usu�rio.

		function forge_sample() : result type none {
 			hefesto.sys.forge("foolib", "local_deps.hsl", "--user-includes-home=../alt_incs --pre-submit-me");
 			if (hefesto.sys.last_forge_result() == 0) {
  				hefesto.sys.echo("foolib built with success.\n");
 			} else {
  				hefesto.sys.echo("unable to build foolib.\n");
  				hefesto.sys.exit(1);
 			}
		}

##### ++byref()++

Atualiza os valores de um argumento local de fun��o para uma vari�vel externa que foi passada como esse argumento. Deve ser passada a vari�vel local exata que deve ser atualizada para a vari�vel externa.

		function caller() : result type none {
 			var return type string;
 			$return = "foo";
 			hefesto.sys.echo($return);
 			byref_sample($return);
 			hefesto.sys.echo($return + "\n");
		}
		function byref_sample(io_var type string) : result type none {
 			$io_var = "bar";
 			hefesto.sys.byref($io_var);
		}

##### ++time()++

Retorna uma ``string`` representando o tempo do sistema de acordo com o formato passado. Os formatos aceitos s�o os mesmos aceitos pela fun��o ``strftime()`` contida na ``libc`` de seu ``OS``.

		function time_sample() : result type none {
 			hefesto.sys.echo("Current time: " + hefesto.sys.time("%H:%M") + "\n");
		}

##### ++setenv()++

Cria uma vari�vel de ambiente. Ap�s o t�rmino do processo a vari�vel � perdida.

		function setenv_sample() : result type none {
 			hefesto.sys.setenv("mytempvar", "mytempval");
		}

No ``Windows`` voc� pode utilizar essa ``syscall`` para acessar o registro tamb�m, bastando informar o caminho completo onde deseja salvar o valor, precedendo essa informa��o pelo marcador ``WINREG:``.

		function setenv_sample() : result type none {
 			hefesto.sys.setenv("WINREG:HKCU\\Software\\Abc\\mytempvar:REG_SZ", "mytempval");
		}

##### ++unsetenv()++

Remove uma vari�vel de ambiente. O processo de remo��o somente afeta o processo referente a aplica��o.

		function unsetenv_sample() : result type none {
 			hefesto.sys.unsetenv("VSCOMPILERPATH");
		}


No ``Windows`` voc� pode utilizar essa syscall para remover valores do registro tamb�m (essa remo��o � permanente). Da seguinte forma:

		function unsetenv_sample() : result type none {
 			hefesto.sys.unsetenv("WINREG:HKLM\\Software\\Abc\\mytempvar");
		}

##### ++call_from_module()++

Chama uma fun��o implementada numa biblioteca din�mica.

O m�dulo precisa conter fun��es implementadas utilizando uma estrutura de dados especial. Mais informa��es sobre isso podem ser encontradas no documento destinado a especificar os detalhes de implementa��o de m�dulos para o hefesto.

		function call_from_module_sample() : result type none {
 			hefesto.sys.call_from_moduke("/usr/share/mymods/my_killer_mod.so", "killer_func", "arg1", "arg2", 3);
		}

Voc� pode usar indire��o de paths para localizar um m�dulo, caso n�o queira indicar o ``path`` completo para ele em seu c�digo ``HSL``:

		function call_from_module_sample() : result type none {
 			hefesto.sys.call_from_module("~/my_killer_mod.so", "killer_func", "arg1", "arg2", 3);
		}

Nesse exemplo apresentado, a biblioteca ``"my_killer_mod.so"`` ser� procurada nos ``paths`` configurados na vari�vel de ambiente ``HEFESTO_MODULES_HOME``.

##### ++get_func_addr()++

Obt�m o endere�o de um nome de fun��o informado.

		function get_func_addr_sample() : result type int {
 			result hefesto.sys.get_func_addr("dummy_clbk");
		}

##### ++call_func_addr()++

Tenta fazer uma chamada de fun��o � partir de um endere�o espec�fico. Se qualquer erro ocorrer no processo um erro de tempo de execu��o � disparado.

		function call_func_addr_sample() : result type int {
 			var clbk_p type int;
 			$clbk_p = hefesto.sys.get_func_addr("abc_one_two_three");
 			result hefesto.sys.call_from_addr($clbk_p, "abc", 1, "two", 3);
		}

### Os facilitadores dos tipos *list* e *string*

Talvez voc� fique tentado(a) em chamar os facilitadores de m�todos, por�m, a ``HSL`` n�o � uma Linguagem orientada � objetos, de forma que os facilitadores podem ser entendidos como opera��es comuns de serem feitas sobre esses tipos de dados e que por serem comuns por motivos de performance foram implementadas de forma *built-in* na ``HSL``.

A **Tabela 5** traz uma listagem dos facilitadores presentes no tipo ``string``. A **Tabela 6** re�ne os facilitadores implementados no tipo ``list``.

**Tabela 5**: Os facilitadores ``string-type``.

| **Facilitador** | **Utilidade**                                 |**Exemplo de chamada**         |
|:---------------:|----------------------------------------------:|:-----------------------------:|
|   ``at``        | Retorna o *byte* presente no �ndice fornecido | $str.at(0)                    |
|   ``len``       | Retorna o tamanho da *string*                 | $str.len()                    |
|   ``match``     | Busca por um padr�o *regex* dentro da *string*| $str.match(".*")              |
|   ``replace``   | Substitui um padr�o *regex* dentro da *string*| $str.replace(".*", "nothing") |

**Tabela 6**: Os facilitadores ``list-type``.

| **Facilitador**  | **Utilidade**                                                     | **Exemplo de chamada**                  |
|:----------------:|------------------------------------------------------------------:|:---------------------------------------:|
| ``item``         | Retorna o item presente no �ndice passado                         | $lst.item(0)                            |
| ``count``        | Retorna o total de itens presentes na lista                       | $lst.count()                            |
| ``add_item``     | Adiciona um item                                                  | $lst.add_item("1")                      |
| ``del_item``     | Remove um item baseado no conte�do passado                        | $lst.del_item("1")                      |
| ``del_index``    | Remove o item presente no �ndice passado                          | $lst.del_index(1)                       |
| ``ls``           | Carrega os *paths* de arquivos que se encaixam na *regex* passada | $lst.ls(".*\\\\.c$")                    |
| ``clear``        | Limpa a lista                                                     | $lst.clear()                            |
| ``index_of``     | Retorna o �ndice de um conte�do passado ou -1                     | $lst.index_of("1")                      |
| ``swap``         | Altera a posi��o de dois items baseados nos seus �ndices          | $lst.swap(0,9)                          |

#### Exemplos usando esses facilitadores

Seguem alguns:

	function get_filepaths_from_directories(dir type list, regex type string) :
    															return type list {
    	var d type int;
        var dirpath type string;
        var oldcwd type string;
        var retval type list;
        $oldcwd = hefesto.sys.pwd();
        $d = 0;
        while ($d < $dir.count()) {
        	$dirpath = $dir.item($d);
        	if (hefesto.sys.cd($dirpath) == 1) {
            	$retval.ls($regex);
            }
            $d = $d + 1;
        }
        hefesto.sys.cd($oldcwd);
        result $retval;
    }

Exemplo de chamada:
>``var dir type list;``
>
>``var os_name type string;``
>
>``$os_name = hefesto.sys.os_name();``
>
>``$dir.add_item(".");``
>
>``$dir.add_item("native/" + $os_name);``
>
>``$dir.add_item("native/" + $os_name + "/fs");``
>
>``$dir.add_item("native/" + $os_name + "/net");``
>
>``$dir.add_item("native/" + $os_name + "/mm");``
>
>``$dir.add_item("native/" + $os_name + "/ps");``
>
>``$dir.add_item("common/");``
>
>``$dir.add_item("common/fs");``
>
>``$dir.add_item("common/net");``
>
>``$dir.add_item("common/mm");``
>
>``$dir.add_item("common/ps");``
>
>``var files type list;``
>
>``$files = get_filepaths_from_directories($dir, "*.\\.c$");``


	function piglatinize(said type string) : result type string {
    	var s type int;
        var etvalray type string;
        var punctoken type list;
        var curr_symbol type string;
        var curr_word type string;

		if ($said.match("[0123456789]") == 1) {
        	hefesto.sys.echo("ANICPAY: I can't handle numbers... aieeeeeeee!!\n");
            result "(ullnay)"; # no way: "nil" is not piglatin!!!! :D
        }

        $punctoken.add_item(" ");
        $punctoken.add_item(",");
        $punctoken.add_item(";");
        $punctoken.add_item(".");
        $punctoken.add_item("?");
        $punctoken.add_item("!");
        $s = 0;
        while ($s < $said.len()) {
        	$curr_symbol = $said.at($s);
			if (($s + 1) == $said.len()) {
				if ($punctoken.index_of($curr_symbol) == -1) {
					$curr_word = $curr_word + $curr_symbol;
					$curr_symbol = ".";
				}
			}
        	if ($punctoken.index_of($curr_symbol) > -1) {
            	if ($curr_word.len() > 1) {
            		var first_letter type string;
                	var second_letter type string;
                	$first_letter = $curr_word.at(0);
                	$second_letter = $curr_word.at(1);
                    var ss type int;
                    $ss = 2;
                    $etvalray = $etvalray + $second_letter;
                    while ($ss < $curr_word.len()) {
                    	$etvalray = $etvalray + $curr_word.at($ss);
                        $ss = $ss + 1;
                    }
                    $etvalray = $etvalray + tolower($first_letter);
                } else {}
                	$etvalray = $etvalray + $curr_word;
                }
				if ($curr_word.len() > 0) {
					$etvalray = $etvalray + "ay";
				}
				$etvalray = $etvalray + $curr_symbol;
				$curr_word = "";
            } else {
            	$curr_word = $curr_word + $said.at($s);
            }
            $s = $s + 1;
        }
		result $etvalray;
    }

    function tolower(l type string) : result type string {
    	var letters type list;
        $letters.add_item("A");
        $letters.add_item("B");
        $letters.add_item("C");
        $letters.add_item("D");
        $letters.add_item("E");
        $letters.add_item("F");
        $letters.add_item("G");
        $letters.add_item("H");
        $letters.add_item("I");
        $letters.add_item("K");
        $letters.add_item("K");
        $letters.add_item("L");
        $letters.add_item("M");
        $letters.add_item("N");
        $letters.add_item("O");
        $letters.add_item("P");
        $letters.add_item("Q");
        $letters.add_item("R");
        $letters.add_item("S");
        $letters.add_item("T");
        $letters.add_item("U");
        $letters.add_item("V");
        $letters.add_item("W");
        $letters.add_item("X");
        $letters.add_item("Y");
        $letters.add_item("Z");
        $letters.add_item("a");
        $letters.add_item("b");
        $letters.add_item("c");
        $letters.add_item("d");
        $letters.add_item("e");
        $letters.add_item("f");
        $letters.add_item("g");
        $letters.add_item("h");
        $letters.add_item("i");
        $letters.add_item("j");
        $letters.add_item("k");
        $letters.add_item("l");
        $letters.add_item("m");
        $letters.add_item("n");
        $letters.add_item("o");
        $letters.add_item("p");
        $letters.add_item("q");
        $letters.add_item("r");
        $letters.add_item("s");
        $letters.add_item("t");
        $letters.add_item("u");
        $letters.add_item("v");
        $letters.add_item("w");
        $letters.add_item("x");
        $letters.add_item("y");
        $letters.add_item("z");
        var l_index type int;
        $l_index =  $letters.index_of($l);
        if ($l_index > -1 && $l_index < 26) {
        	var lower_letter type string;
            $lower_letter = $letters.item($l_index + 26);
            result $lower_letter;
        }
        result $l;
    }

Exemplo de chamada:

>``hefesto.sys.echo(piglatinize("I like to speak pig latin.") + "\n");``

### O subsistema *project*

Esse subsistema re�ne informa��es sobre o projeto de forja atualmente executado pelo *Hefesto* e pode ser acessado de qualquer ponto da forja, ou seja, de dentro do ``toolset``, de fora, n�o importa.

As fun��es apresentadas na **Tabela 7** podem ser acessadas � partir de:

>``hefesto.project.<function-name>(<args>)``

**Tabela 7**: Fun��es presentes no subsistema ``project``.

|    **Fun��o**    |                 **Utilidade**                             |    **Exemplo de chamada**       |
|:----------------:|:---------------------------------------------------------:|--------------------------------:|
|  ``name()``      | Retorna o nome do projeto em execu��o                     | ``hefesto.project.name()``      |
|  ``toolset()``   | Retorna o nome do toolset usado                           | ``hefesto.project.toolset()``   |
|  ``dep_chain()`` | Retorna a ``dep-chain`` usada                             | ``hefesto.project.dep_chain()`` |
|   ``abort()``    | Aborta o projeto                                          | ``hefesto.project.abort(1)``    |
|  ``cmdline()``   | Retorna a linha de comando que a forja est� sendo baseada | ``hefesto.project.cmdline()``   |

### Tem uma forma f�cil de rodar esses exemplos e brincar com a Linguagem para eu me habituar?!

Sim, claro! Quando voc� instala o ``Hefesto`` juntamente com os ``toolsets`` padr�o ele instala um ``toolset`` [oco](https://github.com/rafael-santiago/helios/blob/master/src/include/doc/toolsets/null/README.md), a fun��o de forja apenas retona o n�mero que voc� passa na declara��o do projeto. Com isso, voc� pode chamar o que quiser dentro dos ``entry-points`` do projeto que criar baseado nesse ``toolset-stub``.

### Onde posso continuar explorando a *HSL*?

A ``HSL`` possui um reposit�rio pr�prio de c�digos chamado [Helios](https://github.com/rafael-santiago/helios.git), ele inclusive foi baixado junto com o reposit�rio do ``Hefesto`` em sua m�quina e uma parte que julgo b�sica dele j� est� instalada. Por padr�o, ele traz documenta��es acerca de seus m�dulos. � uma boa dar uma lida nesses documentos caso queira saber mais sobre fun��es de apoio que voc� j� possui � sua disposi��o. Em termos pr�ticos, o ``Helios`` pode ser entendido como o diret�rio de ``includes`` do ``Hefesto`` criado na c�pia que voc� instalou.

Existe uma cole��o de c�digos dentro do *Helios* que s�o as [hc-functions](https://github.com/rafael-santiago/helios/blob/master/src/include/doc/hc/README.md), com elas � poss�vel verificar se o ambiente onde ser� executada a forja possui todos os requisitos necess�rios para isso. Essa bibliotecas de fun��es ``HSL`` permite que voc� crie um *build* mais "parrudo". Seria interessante para quem deseja uma toler�ncia maior para diferentes *build-environments*, de forma a ter um *build* mais no estado da arte.

### Tirando as rodinhas: criando *Hefesto toolsets* e dominando completamente o *build-system*

Se voc� leu as outras se��es e tentou rodar os exemplos, falta um passo para voc� se tornar um usu�rio avan�ado do ``Hefesto``, porque at� o momento voc� est� apto(a) em automatizar passos no sua pr�pria *build-task* e usar os ``toolsets`` "de f�brica". O que te garante o ``status`` de usu�rio final estando ainda dependente de um [``toolset devel``](http://en.wikipedia.org/wiki/Tasmanian_Devil_(Looney_Tunes)).

Nisso, eu te convido a aprender como se implementa um ``Hefesto toolset``. Se voc� at� o momento est� gostando da proposta do aplicativo, ap�s as informa��es contidas nessa se��o, talvez goste mais e se sinta motivado(a) em criar extens�es para ele, levando em considera��o suas pr�prias necessidades (o que � uma das principais linhas mestras desse projeto. *Liberdade para criar*. *Clareza em se expressar*. *Generalidade ao usar*.).

#### Mas antes: uma breve recapitula��o de tudo que j� foi visto

O que voc� j� conferiu e/ou j� sabe:

- O ``Hefesto`` � um *build system* que busca dar clareza e liberdade para escrever de forma organizada uma *build-task*.
- Ele implementa uma *dsl* que � usada tanto nas extens�es que podem ser feitas em uma *build-task* espec�fica quanto nas generalidades que englobam qualquer *build-task* do mesmo tipo, neste caso tais generalidades nele s�o denominadas ``toolsets``.
- Foi apresentada a parte da ``HSL`` que recai sobre a declara��o de um projeto.
- Foram apresentados c�digos exemplificando o reuso de ``toolsets`` previamente escritos.
- Tamb�m foram apresentadas diferentes formas de disparar o *build* (forja) de um projeto.
- Foi visto como monitorar mudan�as nos arquivos que comp�em um projeto.
- Uma vis�o geral, no contexto de usu�rio, sobre as ``dep-chains`` foi apresentada.
- Foi mostrado como incluir passos adicionais ao processo de forja, sendo usado para isso o exemplo da necessidade de se disparar e avaliar o resultado de *unit tests*.
- A possibilidade de se criar um *Forgefile* mais male�vel cuja a escolha de um ``toolset`` espec�fico � feita em *runtime*, tamb�m foi vista.
- Aspectos gerais sobre a ``HSL`` e seu subsistema ``sys`` foram detalhados.

O que voc� ainda n�o conhece e depois de ler essa parte poder� dominar:

- Como declarar um ``toolset``.
- O subsistema ``toolset``.
- Como internamente o ``Hefesto`` sabe que um arquivo mudou.
- O subsistema ``project``.
- Boas pr�ticas para se criar e manter novos ``toolsets``.

#### Nossa meta: um *toolset GCC* para compilar e gerar *aplicativos* escritos em *C*

Escolhi a Linguagem *C* por se tratar de uma Linguagem "compilada" e com depend�ncias a serem resolvidas de forma externa ao compilador. Algumas Linguagens mais contempor�neas detectam essas depend�ncias entre arquivos automaticamente, j� a Linguagem *C* n�o, isso vai nos fazer pensar em muitos detalhes o que ser� um �timo **batismo de fogo no Hades** ;) e a�? Pronto(a)?!

##### Descobrindo quem depende de quem...

Sim, seria bom que voc� para essa segunda parte trouxesse uma no��o de *C*, mesmo que *newbie*. Estou levando em conta que o leitor dessa se��o tem esse perfil.

Imagine um projeto em *C* cuja a fun��o ``main`` � essa:

		#include "init.h"
        #include "config.h"
        #include "options.h"
        #include <stdio.h>

        int main(int argc, char **argv) {
            if (argc > 1) {
            	get_options(argv, argc);
            }
            if (do_config()) {
            	printf("*** Started!\n");
            	return init();
            }
            printf("*** Error.\n");
            return 1;
        }

Em *C* os ``includes`` dizem muito sobre as depend�ncias diretas que um arquivo possui em rela��o aos outros. Geralmente, arquivos inclu�dos usando aspas duplas recaem sobre arquivos locais ao projeto e arquivos que utilizam o padr�o ``< ... >`` s�o arquivos externos ao projeto.

� partir disso, vamos compor uma fun��o que chegar� � conclus�o da ``depchain`` de qualquer projeto *C* que use esses moldes cl�ssicos de inclus�o de c�digos. Convenhamos que indicar depend�ncias manualmente � muito chato, contudo, esteja avisado(a) que a busca por depend�ncias entre arquivos � algo heur�stico de modo que n�o existe uma solu��o geral e completa. Eu pesquisei um pouco al�m da conta sobre isso durante a escrita do ``Hefesto`` e foi algo que at� certo ponto tirou meu sono.

Qual � melhor forma na ``HSL`` de serializar o conte�do de um arquivo em linhas? Eu voto na ``syscall lines_from_file()``. Vou apresentar o c�digo completo do ``c-scanner`` de depend�ncias e depois discorro sobre o que achar relevante:

	include ~/fsutil.hsl

	function get_c_cpp_deps() : result type string {
    	var files type list;
    	var includes type list;
    	var f type int;
    	var i type int;
    	var dep_chain type string;
    	var str type string;
    	var cwd type string;
    	var exts type list;
    	var e type int;
    	var dep_nr type int;
    	var related_files type list;

    	$e = 0;

    	$exts.add_item("h");
    	$exts.add_item("hpp");
    	$exts.add_item("c");
    	$exts.add_item("C");
    	$exts.add_item("CC");
    	$exts.add_item("cc");
    	$exts.add_item("cpp");
    	$exts.add_item("CPP");

    	while ($e < $exts.count()) {
        	$str = ".*\\." + $exts.item($e) + "$";
        	$files.ls($str);
        	$f = 0;
        	$cwd = hefesto.sys.pwd();
        	while ($f < $files.count()) {
            	$str = $files.item($f);
	            $dep_chain = $dep_chain + $str + ": ";
    	        $includes = hefesto.sys.lines_from_file($str, "#include.*$");
        	    $i = 0;
            	$dep_nr = 0;
            	while ($i < $includes.count()) {
                	$str = $includes.item($i);
                	$str.replace(".*#include.*(\"|<)", "");
                	$str.replace("(\"|>)$", "");
                	if (isfile($str) == 1) {
                    	$str = hefesto.sys.make_path($cwd, $str);
                    	if ($dep_nr > 0) {
                        	$dep_chain = $dep_chain + "& ";
                    	}
                    	$dep_chain = $dep_chain + $str + " ";
                    	$dep_nr = $dep_nr + 1;
               	 	}
                	$i = $i + 1;
            	}
            	if ($exts.item($e) == "h" || $exts.item($e) == "hpp") {
                	$str = $files.item($f);
                	$str = filenamefrompath($str);
                	$str.replace("\\.(h|hpp)$", "");
	                $related_files.clear();
    	            $related_files.ls(".*" + filenamefrompath($str) + "\\.(c|C|CC|cc|cpp|CPP)$");
        	        if ($related_files.count() > 0) {
            	        $i = 0;
                	    while ($i < $related_files.count()) {
                    	    if ($dep_nr > 0) {
	                            $dep_chain = $dep_chain + "& ";
    	                    }
	                        $dep_chain = $dep_chain + $related_files.item($i) + " ";
    	                    $dep_nr = $dep_nr + 1;
        	                $i = $i + 1;
            	        }
                	}
            	}
            	$dep_chain = $dep_chain + ";\n";
            	$f = $f + 1;
        	}
        	$files.clear();
        	$e = $e + 1;
    	}
    	result $dep_chain;
	}

Sim, *parser* � algo trabalhoso por mais bobo que seja pois envolve dar suporte para algumas caracter�sticas encantadoras nos seres humanos: bagun�a, desmanzelo e falta de padr�o.

As linhas:

		$exts.add_item("h");
    	$exts.add_item("hpp");
    	$exts.add_item("c");
    	$exts.add_item("C");
    	$exts.add_item("CC");
    	$exts.add_item("cc");
    	$exts.add_item("cpp");
    	$exts.add_item("CPP");

S�o respons�veis por registrar as extens�es de arquivo relevantes de serem escaneados. Pelo fato de haver milh�es de possibilidade para se nomear ``headers`` e ``implementation files`` precisamos de uma lista... Se o desenvolvedor usar ``Hpp`` e/ou ``Cpp`` hahah ele j� era. Poder�amos tamb�m converter o ``filepath`` de um arquivo totalmente para min�sculas ou mai�sculas mas n�o quis fazer isso, se quiser, sinta-se livre.

Depois para cada extens�o registrada, buscamos no diret�rio corrente via a fun��o de lista ``ls()`` o seguinte padr�o ``Regex``:

	$str = ".*\\." + $exts.item($e) + "$";

O que nas itera��es poder� ser:

> ".*\\\\.h$"...
> > ".*\\\\.hpp$"...
> > > ".*\\\\.c$"...
> > > > ".*\\\\.C$"...

Cada arquivo encontrado passa possuir um registro na ``dep-chain`` (lembra da sintaxe dela? ent�o...). Dessa forma ele ter� o conte�do monitorado pelo ``Hefesto``:

	$str = $files.item($f);
	$dep_chain = $dep_chain + $str + ": ";

Depois o conte�do desse arquivo � varrido em busca de diretivas includes:

	$includes = hefesto.sys.lines_from_file($str, "#include.*$");

Note que n�o � uma boa ancorar a ``regex`` com o ``^``, pois pessoas tendem ser relapsas e digitarem ``includes`` nesse formato organizado:

>      #includes "aqui.h"
>               #include "lah.h"
>        /*vou incluir ali tamb�m*/ #include "ali.h"

Com cada linha include encontrada, � extra�do o nome do arquivo e gerado um ``fullpath`` com esse nome extra�do precedido pelo [``cwd``](http://en.wikipedia.org/wiki/Working_directory). Se esse arquivo for realmente acess�vel ele entra como uma depend�ncia para o arquivo anteriormente registrado na ``dep-chain``:

	while ($i < $includes.count()) {
    	$str = $includes.item($i);
       	$str.replace(".*#include.*(\"|<)", "");
       	$str.replace("(\"|>)$", "");
       	if (isfile($str) == 1) {
       		$str = hefesto.sys.make_path($cwd, $str);
            if ($dep_nr > 0) {
            	$dep_chain = $dep_chain + "& ";
            }
            $dep_chain = $dep_chain + $str + " ";
            $dep_nr = $dep_nr + 1;
        }
        $i = $i + 1;
	}

Para os ``headers`` essa fun��o aplica uma busca secund�ria pelos arquivos de implementa��o deles. Se existirem e forem acess�veis sob o contexto do ``cwd`` as implementa��es tamb�m ser�o depend�ncias, no caso, impl�citas, de nosso arquivo atualmente escaneado:

	if ($exts.item($e) == "h" || $exts.item($e) == "hpp") {
    	$str = $files.item($f);
        $str = filenamefrompath($str);
        $str.replace("\\.(h|hpp)$", "");
	    $related_files.clear();
    	$related_files.ls(".*" + filenamefrompath($str) + "\\.(c|C|CC|cc|cpp|CPP)$");
        if ($related_files.count() > 0) {
        	$i = 0;
            while ($i < $related_files.count()) {
            	if ($dep_nr > 0) {
	            	$dep_chain = $dep_chain + "& ";
    	        }
	            $dep_chain = $dep_chain + $related_files.item($i) + " ";
    	        $dep_nr = $dep_nr + 1;
        	    $i = $i + 1;
            }
        }
	}

Depois disso, o arquivo atual j� ter� todas as poss�veis depend�ncias devidamente listadas na ``dep-chain`` o que apenas resta fechar a declara��o de suas depend�ncias:

	$dep_chain = $dep_chain + ";\n";

Isso � repetido com cada arquivo presente no ``cwd``, em outras palavras o diret�rio do projeto, ou o diret�rio atual de onde esse ``c-scanner`` de depend�ncias foi chamado, note que � poss�vel mudar o ``cwd`` com a ``syscall cd`` e ent�o chamar o ``scanner``.

Ap�s todos os arquivos processados a ``dep-chain`` composta retorna para o chamador:

		result $dep_chain;

A qual provavelmente ser� usada na se��o ``dependencies`` presente na declara��o de um projeto.

Caso queira, volte na listagem total do c�digo comentado e tente diger�-lo um pouco mais. At� se sentir confiante sobre o que cada linha faz.

##### Criando o toolset

Um ``toolset`` precisa ser declarado. Na declara��o de um ``toolset`` n�o apenas definimos por qual nome esse ser� chamado, mas tamb�m reunimos em sua declara��o de forma geral tudo que ele far� usando ferramentas externas.

O que um ``toolset`` *C* precisa fazer que depende de ``tools`` externas?

- Compilar os c�digos;
- Linkedit�-los;

Veja a declara��o desse ``toolset``:

	include ~/toolsets/gcc/forges/gcc_c_app_forge.hsl

	toolset "gcc-c-app" forge function "gcc_c_binary_forge" :
    	forge helpers "gcc_compile_source_list",
        			  "gcc_link_ofiles", "gcc_mk_app_compilation_command":
    	command "compile_r": SOURCE, OUTFILE, INCLUDES, CFLAGS <
        	gcc -c $SOURCE $INCLUDES $CFLAGS -o $OUTFILE
    	>
	    command "compile_d": SOURCE, OUTFILE, INCLUDES, CFLAGS <
    	    gcc -g -c $SOURCE $INCLUDES $CFLAGS -o $OUTFILE
    	>
    	command "link_shared": APPNAME, OBJECTS, LIBRARIES, LDFLAGS <
        	gcc -o$APPNAME $OBJECTS $LIBRARIES $LDFLAGS
    	>
    	command "link_static": APPNAME, OBJECTS, LIBRARIES, LDFLAGS <
        	gcc -static -o$APPNAME $OBJECTS $LIBRARIES $LDFLAGS
    	>
	$

A sintaxe b�sica de declara��o �:

>``toolset <string-name> forge function <hsl-function-name> : [forge helpers <helpers-list>] : <command-templates> $``

No exemplo apresentado, o ``toolset`` se chama: ``gcc-c-app``. Sua fun��o de forja � ``gcc_c_binary_forge``, isso explica a diretiva ``include`` no in�cio do exemplo, pois � nele que est� definida a fun��o de forja em quest�o. Os ajudantes de forja (fun��es ``HSL``) s�o: ``gcc_compile_list``, ``gcc_link_ofiles`` e ``gcc_mk_compilation_command``. Uma declara��o de ``toolset`` sempre termina com o s�mbolo de final de fita (``$``).

Os ``templates de comando`` que esse ``toolset`` implementa s�o: ``compile_r``, ``compile_d``, ``link_shared`` e ``link_static``. Um template de comando nada mais � do que uma abstra��o de um comando externo que o seu ``toolset`` ir� montar. Segue a sintaxe de declara��o dessa parte:

>``command <string-name> : <string-argument-list> < <command-line template> >``

Importante notar que um ``comando de toolset`` **sempre** recebe *strings* como argumento e retorna uma *string*, baseada em seu ``command-line template`` com os argumentos passados expandidos nele.

Existe uma regra bem estrita quanto a acessibilidade desses comandos de ``toolset``:

>Somente podem ser acessados pela fun��o de forja do ``toolset`` ou pelas fun��es ajudantes de forja.

Mas agora, como acessar esses comandos de ``toolset``?

Muito simples, voc� os acessa � partir do subsistema ``toolset``. Imagine o ``toolset`` apresentado, para acessar o comando ``compile_r`` � necess�rio:
>(...)
>``$cmd = hefesto.toolset.compile_r($source_path, $outfile_path, $includes, $cflags);``
>(...)

Uma boa abordagem no in�cio da cria��o de um ``toolset`` � se perguntar quais comandos externos esse ``toolset`` necessitar� executar. Acho que essa � a g�nese de qualquer ``toolset``.

##### A fun��o de forja

Talvez essa seja a parte mais trabalhosa do trajeto, pois � na fun��o de forja que deve ser incutida a l�gica do *build*. Levando em considera��o que um ``toolset`` deve ser uma generaliza��o de tarefas que usem os comandos externos do ``toolset`` para produzirem alguma coisa e ainda serem utilizados por mais de uma pessoa...

Segue a fun��o de forja, depois da listagem, comentarei as partes que julgar relevantes:

	function gcc_c_binary_forge(SOURCES type list,
    							INCLUDES type list, CFLAGS type list,
                                LIBRARIES type list,
                                LDFLAGS type list,
                                APPNAME type string) : result type int {
    	var exit_code type int;
    	var includes type string;
    	var cflags type string;
    	var libraries type string;
    	var ldflags type string;
    	var objects type string;

        if ($SOURCES.count() == 0) {
            if (hefesto.project.toolset() == "gcc-c-app") {
                $SOURCES.ls(".*\\.c$");
            } else {
                $SOURCES.ls(".*\\.(cc|cpp|CC|Cpp|CPP)$");
            }
        }

        if ($SOURCES.count() == 0) {
            hefesto.sys.echo("\t(empty source list)\n");
            result 1;
        }

        var obj_output_dir type list;
        var obj_dir type string;

        $obj_output_dir = hefesto.sys.get_option("obj-output-dir");
        if ($obj_output_dir.count() > 0) {
            $obj_dir = $obj_output_dir.item(0);
            mktree($obj_dir);
        } else {
            $obj_dir = hefesto.sys.pwd();
        }

        var bin_output_dir type list;
        var bin_output type string;

        $bin_output_dir = hefesto.sys.get_option("bin-output-dir");
        if ($bin_output_dir.count() > 0) {
            $bin_output = $bin_output_dir.item(0);
            mktree($bin_output);
            $bin_output = hefesto.sys.make_path($bin_output, $APPNAME);
        } else {
            $bin_output = $APPNAME;
        }

        $exit_code = 0;

		#  GCC's include list option string
        $includes = gcc_mk_gcc_incl_str_opt($INCLUDES); 

        $cflags = gcc_mk_raw_str_opt($CFLAGS); #  GCC's compile options

        var cpu_arch type list;
        var chosen_arch type string;
        $cpu_arch = hefesto.sys.get_option("cpu-arch");
        $chosen_arch = "";
        if ($cpu_arch.count() > 0) {
            $chosen_arch = $cpu_arch.item(0);
            if ($chosen_arch != "32" && $chosen_arch != "64") {
                hefesto.sys.echo(hefesto.project.toolset() +
                	" fatal error: invalid value for cpu-arch " +
                    "option must be '32' or '64'.\n");
                result 1;
            }
            $cflags = $cflags + " -m" + $chosen_arch;
        }

        #  compiling...
        hefesto.sys.echo("*** compiling...\n");

        $exit_code = gcc_compile_source_list($SOURCES, $includes, $cflags, $obj_dir); 
        if ($gcc_c_project_forge_dirty_files_nr == 0 && isfile($bin_output) == 0) {
            $gcc_c_project_forge_dirty_files_nr = 1;
        }

        if ($gcc_c_project_forge_dirty_files_nr > 0 && $exit_code == 0) {
            $objects = gcc_mk_ofiles_str_opt($SOURCES, $obj_dir);
            $ldflags = gcc_mk_raw_str_opt($LDFLAGS);
            if ($chosen_arch.len() > 0) {
                $ldflags = $ldflags + "-m" + $chosen_arch;
            }
            $libraries = gcc_mk_gcc_lib_str_opt($LIBRARIES);
            #  linking...
            hefesto.sys.echo("*** now linking...\n\t*** waiting...\n");
            $exit_code = gcc_link_ofiles($objects,
            							 $libraries
                                         $ldflags,
                                         $bin_output);
        }

        if ($exit_code == 0) {
            hefesto.sys.echo("*** success.\n");
        } else {
            hefesto.sys.echo("*** failure.\n");
        }

        result $exit_code;
    }

Note que a fun��o de forja tem a seguinte defini��o:

	function gcc_c_binary_forge(SOURCES type list,
    							INCLUDES type list, CFLAGS type list,
                                LIBRARIES type list,
                                LDFLAGS type list,
                                APPNAME type string) : result type int

Isso explica a sequ�ncia/tipo dos argumentos passados na declara��o do projeto:

	var sources type list;
    var includes type list;
    var cflags type list;
    var libraries type list;
    var ldflags type list;

	project sample : toolset "gcc-c-app" : $sources, $includes, $cflags,
                                           $libraries, $ldflags, "sample" ;

Esse ``toolset`` possui de cara uma conveni�ncia:

	if ($SOURCES.count() == 0) {
        if (hefesto.project.toolset() == "gcc-c-app") {
        	$SOURCES.ls(".*\\.c$");
        } else {
        	$SOURCES.ls(".*\\.(cc|cpp|CC|Cpp|CPP)$");
    	}
    }

Se for passada uma lista de c�digos vazia, ele escaneia o diret�rio corrente por c�digos *C* ou *CC*. Pelo fato da mesma fun��o de forja ser usada por outro ``toolset`` (``gcc-cc-app``) respons�vel por criar aplicativos *C++*, verificamos o nome do ``toolset`` atualmente carregado, via o subsistema ``project``, se for "gcc-c-app" listamos todos os arquivos que terminem com ".c" no nome para dentro da lista ``SOURCES``. Caso contr�rio, buscamos por c�digos *C++*.

Se mesmo assim ``SOURCES`` estiver vazia:

	if ($SOURCES.count() == 0) {
    	hefesto.sys.echo("\t(empty source list)\n");
        result 1;
    }

Terminamos aqui, alertando sobre a lista vazia e saindo com ``1`` para sinalizar erro e fazer com que o ``Hefesto`` quebre o processo de forja para que o usu�rio tome conhecimento que algo deu errado.

Mais algumas conveni�ncias... �s vezes por motivos de higiene n�o desejamos poluir o diret�rio de onde o *build* roda com arquivos objeto:

	var obj_output_dir type list;
    var obj_dir type string;

    $obj_output_dir = hefesto.sys.get_option("obj-output-dir");
    if ($obj_output_dir.count() > 0) {
    	$obj_dir = $obj_output_dir.item(0);
        mktree($obj_dir);
    } else {
    	$obj_dir = hefesto.sys.pwd();
    }

Nisso, verificamos se o usu�rio passou a op��o ``--obj-output-dir``. Lembrando que a ``syscall get_option`` retorna uma lista. Se a lista retornada contiver pelo menos um item � porque algo foi realmente passado e neste caso pegamos o primeiro item da lista (que � um *path*, *full* ou relativo) e passamos para a fun��o ``mktree()``, definida em ``fsutil.hsl``. Essa fun��o cria um ``path`` caso esse n�o exista. Agora, se n�o foi passada a op��o ``--obj-output-dir``, o diret�rio corrente � assumido como o *output-dir* para os arquivos objeto, ``hefesto.sys.pwd()`` nos garante isso.

Algo similar � feito com o diret�rio de sa�da para o bin�rio que ser� criado com a forja, confira:

	$bin_output_dir = hefesto.sys.get_option("bin-output-dir");
    if ($bin_output_dir.count() > 0) {
    	$bin_output = $bin_output_dir.item(0);
        mktree($bin_output);
        $bin_output = hefesto.sys.make_path($bin_output, $APPNAME);
    } else {
    	$bin_output = $APPNAME;
    }

Agora � chegada a hora de converter as op��es do compilador em lista para *string*:

		#  GCC's include list option string
        $includes = gcc_mk_gcc_incl_str_opt($INCLUDES);
        $cflags = gcc_mk_raw_str_opt($CFLAGS); #  GCC's compile options

Essas fun��es ser�o detalhadas mais tarde, por hora, s� � importante conhec�-las superficialmente.

Tamb�m conv�m poder escolher a arquitetura do *target*, no caso a leitura de op��o que ser� apresentada permite escolher entre um bin�rio *32-bit* ou *64-bit*, confira:

	var cpu_arch type list;
    var chosen_arch type string;
    $cpu_arch = hefesto.sys.get_option("cpu-arch");
    $chosen_arch = "";
    if ($cpu_arch.count() > 0) {
		$chosen_arch = $cpu_arch.item(0);
		if ($chosen_arch != "32" && $chosen_arch != "64") {
			hefesto.sys.echo(hefesto.project.toolset() +
                    " fatal error: invalid value for cpu-arch " +
                    "option must be '32' or '64'.\n");
			result 1;
        }
	}

Se o usu�rio passar ``--cpu-arch=32`` ou ``--cpu-arch=64``, ser� adicionada a op��o ``-m32`` ou ``-m64`` na linha de comando que ser� diretamente repassada ao *GCC*:

	$cflags = $cflags + " -m" + $chosen_arch;

Essa op��o do *GCC* especifica a arquitetura do *target*. Caso seja passado um valor diferente de ``32`` ou ``64``, a forja ser� interrompida retornando ``1`` que significa erro.

Agora entregamos o controle para a fun��o que propriamente compilar� cada c�digo presente no projeto:

	#  compiling...
    hefesto.sys.echo("*** compiling...\n");

    $exit_code = gcc_compile_source_list($SOURCES, $includes, $cflags, $obj_dir); 

Mais para frente a fun��o ``gcc_compile_source_list()``, ser� detalhada.

Nesse ``toolset`` existe uma vari�vel global chamada ``gcc_c_project_forge_dirty_files_nr``, que guarda a contagem de arquivos efetivamente processados. Se ap�s o final da compila��o n�o houver nenhum arquivo processado, � feita a verifica��o se o *target* (o bin�rio propriamente dito) existe. Caso n�o exista, a vari�vel global de contagem � setada para ``1``.

    if ($gcc_c_project_forge_dirty_files_nr == 0 && isfile($bin_output) == 0) {
    	$gcc_c_project_forge_dirty_files_nr = 1;
    }

O motivo de setar essa vari�vel � por conta de garantir que a *linkedi��o* ser� feita (mesmo sem nenhum arquivo processado, por�m sem o bin�rio devemos *linkeditar*):

	if ($gcc_c_project_forge_dirty_files_nr > 0 && $exit_code == 0) {
		$objects = gcc_mk_ofiles_str_opt($SOURCES, $obj_dir);
        $ldflags = gcc_mk_raw_str_opt($LDFLAGS);
        if ($chosen_arch.len() > 0) {
			$ldflags = $ldflags + "-m" + $chosen_arch;
		}
		$libraries = gcc_mk_gcc_lib_str_opt($LIBRARIES);
		#  linking...
		hefesto.sys.echo("*** now linking...\n\t*** waiting...\n");
		$exit_code = gcc_link_ofiles($objects,
									 $libraries
									 $ldflags,
									 $bin_output);
	}

Note que al�m da contagem de arquivos processados, a *linkedi��o* tamb�m depende de n�o ter havido nenhum erro na compila��o, o ``$exit_code == 0`` na ``if-clause`` nos  garante isso.

Se necess�rio *linkeditar*:

- Os *file paths* correspondentes aos arquivos objeto s�o reunidos numa *string*;
- O mesmo � feito com as op��es de *linker* passadas pelo usu�rio, na declara��o do projeto de forja;
- Se a arquitetura foi explicitada adiciona a op��o *GCC* correspondente nas op��es de *linker*;
- Deserializa tamb�m os file paths adicionais onde podem ser encontradas bibliotecas (isso foi passado pelo usu�rio na declara��o do projeto de forja);
- Chama a fun��o que realiza efetivamente a *linkedi��o*: ``gcc_link_ofiles()``.

Depois apenas um relat�rio de *status* baseado no *exit code*, para orientar o usu�rio:

	if ($exit_code == 0) {
    	hefesto.sys.echo("*** success.\n");
    } else {
    	hefesto.sys.echo("*** failure.\n");
    }

E por fim o retorno do exit code, o que � importante para que o ``Hefesto`` saiba que rumo a forja teve:

	result $exit_code;

Volte na listagem integral do ``source-code`` da fun��o de forja e veja se consegue entender cada por��o de c�digo dela. � importante para prosseguir entender realmente tudo que est� sendo feito.

##### Detalhando cada forge helper

Anteriormente foi detalhada a fun��o de forja, contudo, ela usa um conjunto de fun��es de apoio, as quais aqui ser�o melhor detalhadas.


###### gcc_compile_source_list()

Das ajudantes de forja, talvez a mais "complexa". Por isso, vamos come�ar com ela.

Nessa fun��o voc� ver� como as altera��es dos arquivos s�o monitoradas e que � de responsabilidade do desenvolvedor do ``toolset`` manter a sanidade dessa ``feature``.

Existem dois *branches* de execu��o, um recai sobre a compila��o ++s�ncrona++ o outro sobre a compila��o ++ass�ncrona++. Poderiam ter sido quebradas em duas fun��es, nada impede, mas aqui est�o bifurcadas em *if-branches*.

Uma compila��o **s�ncrona** pode ser entendida como **uma compila��o de arquivo por ciclo**. J� uma compila��o **ass�ncrona** pode ser entendida como ***n* compila��es de arquivos por ciclo**.

Essa � a defini��o da fun��o:

	function gcc_compile_source_list(sources type list,
    								 includes type string,
                                     cflags type string,
                                     obj_dir type string) : result type int

Recebe a lista de c�digos que ser�o compilados, uma ``string`` de diret�rios de *includes*, uma ``string`` com op��es que dever�o ser usadas na compila��o de cada c�digo-fonte e o *path* para o diret�rio onde os arquivos objeto dever�o ser gerados. Retorna zero para processamento sem erro e diferente de zero caso alguma coisa n�o ocorra conforme esperado.

O in�cio da fun��o � esse:

	var size type int;
    var i type int;
    var j type int;
    var exit_code type int;
    var ofile type string;
    var qsize_list type list;
    var run_list type list;
    var qsize type int;
    var not_compiled type list;
    var not_compiled_tmp type list;
    var compile_model type list;
    var is_release type int;
    var curr_src_file type string;

    $size = $sources.count();

    if ($size == 0) result 0;

    $qsize_list = hefesto.sys.get_option("qsize");

    if ($qsize_list.count() > 0) {
        $qsize = $qsize_list.item(0);
    }

Se passado uma lista de c�digos vazia retorna zero logo de cara. Ap�s isso � feita a leitura de uma op��o reconhecida internamente pelo *Hefesto* que � a ``--qsize=n``.

Essa op��o indica o total de processos concorrentes que a ``syscall run`` � capaz de criar por chamada ass�ncrona. Para chamar a ``run`` de forma ass�ncrona � preciso passar uma lista de comandos.

Se a op��o ``--qsize`` for passada, a fun��o guarda o valor passado nela para uso posterior. Logo depois:

	$compile_model = hefesto.sys.get_option("compile-model");

    $is_release = 1;

    if ($compile_model.count() > 0) {
        if ($compile_model.item(0) != "release" &&
            $compile_model.item(0) != "debug") {
            hefesto.sys.echo(hefesto.project.toolset() +
            	" internal error: unknown compile model: \"" +
                $compile_model.item(0) + "\"\n");
            result 1;
        }
        $is_release = ($compile_model.item(0) == "release");
    }

...Lemos a op��o ``compile-model``, se o usu�rio passou essa op��o verifica se � **release** ou **debug**, sendo outro conte�do quebra a forja saindo com *1*. Caso seja um dos dois valores reconhecidos, seta uma *flag* indicando a escolha, para uso posterior.

Agora vem a compila��o propriamente dita:

	$exit_code = 0;
    $i = 0;

    $gcc_c_project_forge_dirty_files_nr = 0;

    $not_compiled = lsdup($sources);

    if ($qsize <= 1) {
        while ($i < $size && $exit_code == 0) {
            $ofile = $sources.item($i);
            $ofile = gcc_mk_ofile_name(filenamefrompath($ofile), $obj_dir);
            if (hefesto.toolset.file_has_change($sources.item($i)) == 1 ||
            	isfile($ofile) == 0) {
                $gcc_c_project_forge_dirty_files_nr =
                	$gcc_c_project_forge_dirty_files_nr + 1;
                $curr_src_file = $sources.item($i);
                $exit_code =
                	hefesto.sys.run(
                      gcc_mk_app_compilation_command($curr_src_file,
													 $ofile,
                                                     $includes,
                                                     $cflags, $is_release
                      )
                    );
                if ($exit_code == 0) {
                    $not_compiled.del_item($sources.item($i));
                    hefesto.sys.echo("\t*** " +
                    		$sources.item($i) +
                            ": no errors found.\n");
                } else {
                    hefesto.sys.echo("\t*** " +
                    		$sources.item($i) + ": errors found!\n");
                }
            } else {
                hefesto.sys.echo("\t*** " + $sources.item($i) + ": no changes.\n");
            }
            $i = $i + 1;
        }
        if ($gcc_c_project_forge_dirty_files_nr > 0) {
            hefesto.toolset.base_refresh($not_compiled);
        }
    } else {
    	(...)
    }

O *else* refere-se a parte ass�ncrona, por hora vamos abstra�-la e nos atermos a parte s�ncrona. Temos a seguinte inicializa��o:

	$exit_code = 0;
	$i = 0;
    $gcc_c_project_forge_dirty_files_nr = 0;
    $not_compiled = lsdup($sources);

A vari�vel que guarda o *exit code* das compila��es � zerada. O contador que percorrer� a lista de c�digos "come�ar� pelo come�o". A *flag* que indica que algum arquivo foi efetivamente processado � *unsetada*. Depois usamos uma fun��o presente em ``lsutil.hsl``. Essa fun��o retorna uma c�pia da lista passada para ela.

A lista ``not_compiled`` tem uma utilidade especial. � por meio dela que o *Hefesto* conseguir� saber qual arquivo realmente mudou entre a �ltima forja e a atual.

Existem duas fun��es *built-in* no ``subsystem toolset``:

- ``hefesto.toolset.file_has_change(<file-path>)``
- ``hefesto.toolset.base_refresh(<untouched-files>)``

A ``file_has_change`` � bem direta:

>Recebe o *path* de um arquivo e retorna **1** caso esse **arquivo tenha mudado**, de outra forma **0**.

J� ``base_refresh()``:

>Recebe uma lista de *paths*, mas essa lista deve apenas conter os *paths* dos arquivos que **ainda n�o foram processados**.

O *workflow* de uso dessas fun��es geralmente se resume em invocar ``file_has_change`` para saber se o arquivo corrente mudou, se mudou, se aplica o processamento necess�rio. Realiza isso para cada arquivo. Ao final, chama apenas uma �nica vez a ``base_refresh``. Com essas duas ``toolset-functions`` o *Hefesto* � capaz de saber exatamente quem mudou desde a �ltima forja.

Voltemos ao c�digo:

	if ($qsize <= 1) {
        while ($i < $size && $exit_code == 0) {
            $ofile = $sources.item($i);
            $ofile = gcc_mk_ofile_name(filenamefrompath($ofile), $obj_dir);
            if (hefesto.toolset.file_has_change($sources.item($i)) == 1 ||
            	isfile($ofile) == 0) {
                $gcc_c_project_forge_dirty_files_nr =
                	$gcc_c_project_forge_dirty_files_nr + 1;
                $curr_src_file = $sources.item($i);
                $exit_code =
                	hefesto.sys.run(
                      gcc_mk_app_compilation_command($curr_src_file,
													 $ofile,
                                                     $includes,
                                                     $cflags, $is_release
                      )
                    );
                if ($exit_code == 0) {
                    $not_compiled.del_item($sources.item($i));
                    hefesto.sys.echo("\t*** " +
                    		$sources.item($i) +
                            ": no errors found.\n");
                } else {
                    hefesto.sys.echo("\t*** " +
                    		$sources.item($i) + ": errors found!\n");
                }
            } else {
                hefesto.sys.echo("\t*** " + $sources.item($i) + ": no changes.\n");
            }
            $i = $i + 1;
        }
        if ($gcc_c_project_forge_dirty_files_nr > 0) {
            hefesto.toolset.base_refresh($not_compiled);
        }
    }

Se a forja tiver que ser s�ncrona, i.e: se ``qsize`` for igual ou menor a *1*, para cada caminho de arquivo (c�digo *C*) presente na lista, enquanto n�o houver nenhum erro de compila��o:

> � partir do path do arquivo usamos a fun��o ``gcc_mk_ofile_name()`` para criar o nome objeto do arquivo, de fato apenas substitu�mos o ``.c`` por ``.o`` e juntamos esse novo nome com o conte�do do caminho para o diret�rio de arquivos objeto.
>
> Verificamos se o arquivo ``.c`` teve altera��o ou se seu arquivo objeto n�o existe.
>> Com uma dessas duas condi��es satisfeitas, incrementamos o contador de arquivos processados e rodamos o comando de compila��o. Se o arquivo for compilado com �xito, removemos o *path* dele da lista ``not_compiled``.
>>
>> Se o arquivo ``.c`` n�o mudou e o seu objeto existe, apenas informa que n�o houveram mudan�as naquele arquivo.

Ap�s todos os c�digos-fonte processados, se houve efetivamente pelo menos uma compila��o, realiza o ``base-refresh`` e retorna o *exit code* do processo, para que o chamador tome a medida necess�ria baseada nesse valor retornado.

Agora vamos ver a parte ass�ncrona da compila��o:

	else {
        $not_compiled_tmp.clear();
        while ($i < $size) {
            $ofile = $sources.item($i);
            $ofile = gcc_mk_ofile_name(filenamefrompath($ofile), $obj_dir);
            if (hefesto.toolset.file_has_change($sources.item($i)) == 1 ||
            	isfile($ofile) == 0) {
                $gcc_c_project_forge_dirty_files_nr =
                	$gcc_c_project_forge_dirty_files_nr + 1;
                $curr_src_file = $sources.item($i);
                $run_list.add_item(
                	gcc_mk_app_compilation_command($curr_src_file,
                    							   $ofile,
                                                   $includes,
                                                   $cflags,
                                                   $is_release));
                $not_compiled_tmp.add_item($sources.item($i));
            }
            if ($run_list.count() == $qsize) {
                $exit_code = hefesto.sys.run($run_list);
                if ($exit_code == 0) {
                    $j = 0;
                    while ($j < $not_compiled_tmp.count()) {
                        $not_compiled.del_item($not_compiled_tmp.item($j));
                        $j = $j + 1;
                    }
                    $not_compiled_tmp.clear();
                    hefesto.toolset.base_refresh($not_compiled);
                }
                $run_list.clear();
            }
            $i = $i + 1;
        }
        if($run_list.count() > 0) {
            $exit_code = hefesto.sys.run($run_list);
            if ($exit_code == 0) {
                $j = 0;
                while ($j < $not_compiled_tmp.count()) {
                    $not_compiled.del_item($not_compiled_tmp.item($j));
                    $j = $j + 1;
                }
                hefesto.toolset.base_refresh($not_compiled);
            }
        }
    }

O comportamento � similar ao da por��o s�ncrona. Uma diferen�a � que os comandos de compila��o n�o s�o imediatamente executados, sendo eles adicionados a uma lista para execu��o ao final de um ciclo. Outra diferen�a � que aqui h� uma lista auxiliar chamada ``not_compiled_tmp`` que � preenchida por ciclos e o ``base-refreh`` � feito ao final desses ciclos. Um ciclo � completo quando o tamanho de ``run_list``, que � a lista que cont�m os comandos de compila��o ainda n�o executados, contiver o total de elementos igual a ``--qsize``. Se alguma compila��o quebrar ao final de um ciclo, o *loop* ser� interrompido. Se ao final do *loop* n�o havendo erro de compila��o, ainda houverem c�digos por compilar, eles ser�o compilados e o ``base-refresh`` feito.

###### gcc_mk_app_compilation_command()

Essa fun��o � respons�vel por **montar** os comandos de compila��o que ser�o executados:

	local function gcc_mk_app_compilation_command(src_name type string,
    	                                          outfile type string,
        	                                      includes type string,
            	                                  cflags type string,
                            is_release type int) : result type string {
    	var cmd type string;
    	if ($is_release == 1) {
        	$cmd = hefesto.toolset.compile_r($src_name, $outfile, $includes, $cflags);
    	} else {
        	$cmd = hefesto.toolset.compile_d($src_name, $outfile, $includes, $cflags);
    	}
    	result $cmd;
	}

Note que s�o passados para ela todos os par�metros necess�rios para se compilar um fonte no *GCC* com a op��o ``-c`` (confira o *template* dos comandos ``compile_r`` e ``compile_d`` na declara��o do ``toolset``). Note que fora isso, � tamb�m informado o tipo de compila��o, se � desejado incluir informa��es de *debug* ou n�o (em *release* n�o incluir�). Logo ap�s, apenas � retornado a linha de comando formatada, pois um ``toolset-command`` n�o � executado, cabe ao desevolvedor do ``toolset`` escolher a melhor maneira de execut�-lo via a ``syscall run`` e avaliar o *exit code* de tal comando. Lembrando que todos os ``toolset-commands`` est�o dispon�veis para a fun��o de forja e suas ajudantes � partir do subsistema ``toolset`` (``hefesto.toolset.<command>``). Ainda, tudo o que foi passado para o comando se resumiu em argumentos do tipo ``string``. Se existir um lema para um ``toolset-command``, pode ser esse:

>Somente recebe *strings* **na ordem e quantidade** pr�-definidas, somente retorna **uma** *string*.

###### gcc_link_ofiles()

Essa fun��o � respons�vel por *linkeditar* os arquivos objeto produzindo a aplica��o sob o nome que ``appname`` contiver.

Note que o argumento ``objects`` j� � a lista de objetos no formato *string* que o *GCC* espera, i.e: *"foo.o bar.o baz.o"*.

As vari�veis ``libraries`` e ``ldflags`` a mesma coisa, listas no formato *string* que o *GCC* espera.

Lembre que na fun��o de forja nos ocupamos de converter as listas ``HSL`` passadas pelo usu�rio do ``toolset`` para o "formato *string* do *GCC*".

A primeira coisa que essa fun��o de *linking* faz � verificar se a op��o ``--link-model`` foi passada pelo usu�rio. Essa op��o admite dois modos de *linking*: ``static`` ou ``shared``. Se for passado um modo de *linkagem* alien�gena a forja quebrar� com sa�da *1*.

Se um dos modos reconhecidos foi passado (note que o modo padr�o � *shared*), essa fun��o monta o comando de *linking* necess�rio � partir do ``command-template`` correspondente, definido no ``toolset`` e o executa com a ``syscall run``. Retornando ao final o ``exit code`` do processo de *linkedi��o*.

Confira a listagem do c�digo e repasse o que leu:

	function gcc_link_ofiles(objects type string,
                             libraries type string,
                             ldflags type string,
                             appname type string) : result type int {
		var exit_code type int;
    	var link_model type list;
    	var is_static type int;
    	$link_model = hefesto.sys.get_option("link-model");
    	$is_static = 0;
    	if ($link_model.count() > 0) {
        	if ($link_model.item(0) == "static") {
            	$is_static = 1;
        	} else {
            	if ($link_model.item(0) != "shared") {
                	hefesto.sys.echo(hefesto.project.toolset() +
                    		" internal error: unknown link model: \"" +
                            $link_model.item(0) + "\"\n");
                	result 1;
            	}
        	}
    	}
    	if ($is_static == 1) {
        	$exit_code = hefesto.sys.run(
            	hefesto.toolset.link_static($appname,
                							$objects,
                                            $libraries, $ldflags));
    	} else {
 	       $exit_code = hefesto.sys.run(
           	hefesto.toolset.link_shared($appname,
            							$objects,
                                        $libraries, $ldflags));
    	}
    	result $exit_code;
	}

� isso, um bom exerc�cio � tentar criar um ``toolset`` para automatizar algo para o seu estado de coisas. N�o precisa pensar apenas em compiladores, voc� pode tentar criar um ``toolset`` que fa�a o *deploy* do seu pacote, entre outras coisas. Seja criativo(a)!
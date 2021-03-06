#include "controladorasapresentacao.h"
#include <curses.h>

const string DESC="Preencha o campo abaixo:";
const char AVISO[200]="Dados invalidos foram fornecidos, gostaira de tentar novamanete? (y/n)";
char son(){
	char ans;
	while(true){
		ans=getch();
		if(ans=='y' or ans=='n')
			return ans;
	}
}
string invoca_texto(string descricao, string nome){

	clear();
	curs_set(1);
	echo();
	int linha, coluna;
	int linha_win, coluna_win;
	int linha_s, coluna_s;
	char dado[100];
    getmaxyx(stdscr,linha,coluna);
	WINDOW *text_win=newwin(max(linha/10,3),coluna*3/4,( linha/2 ),( coluna/8 ));
    getmaxyx(text_win,linha_win,coluna_win);
	getbegyx(text_win,linha_s,coluna_s);
	char titulo[]="SISTEMA DE INVESTIMENTOS";
	mvprintw(1,(coluna - strlen(titulo))/2,titulo);
	mvprintw(linha_s-1,coluna_s+1,descricao.c_str());
	refresh();
	box(text_win,0,0);
	attron(A_REVERSE);
	mvprintw(linha_s+1,coluna_s+1,nome.c_str());
	attroff(A_REVERSE);
	printw(" ");
	wrefresh(text_win);
	getstr(dado);
	return (string)dado;

}
int invoca_menu(vector<string>& choices){
	clear();
	int linha, coluna;
	int linha_win, coluna_win;
	int choice, size=(int)choices.size();
	curs_set(0);
    getmaxyx(stdscr,linha,coluna);
	WINDOW *menu_win= newwin(max(linha/2,size+4),coluna*3/4,( linha/4 ),( coluna/8 ));
    getmaxyx(menu_win,linha_win,coluna_win);
	keypad(menu_win,true);
	int highlight=0;
	char titulo[]="SISTEMA DE INVESTIMENTOS";
	mvprintw(1,(coluna - strlen(titulo))/2,titulo);
	refresh();
	box(menu_win,0,0);
	wrefresh(menu_win);
	noecho();
	while(1){
		for(int i=0;i<size ;i++){
			if(i==highlight)
				wattron(menu_win,A_REVERSE);
			mvwprintw(menu_win,i+2,2,choices[i].c_str());
			wattroff(menu_win,A_REVERSE);
			printw("\n");

		}
		choice=wgetch(menu_win);
		switch(choice){
			case KEY_UP:
				highlight--;
				if(highlight==-1)
					highlight=size-1;
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight==size)
					highlight=0;
				break;
			default:
				break;
		}
		if(choice==10)
			break;
	}
	return highlight;
}

void mostra_atributos(vector<string>& choices){
	clear();
	int linha, coluna;
	int linha_win, coluna_win;
	int size=(int)choices.size();
	curs_set(0);
    getmaxyx(stdscr,linha,coluna);
	WINDOW *menu_win= newwin(max(linha/2,size+4),coluna*3/4,( linha/4 ),( coluna/8 ));
    getmaxyx(menu_win,linha_win,coluna_win);
	keypad(menu_win,true);
	char titulo[]="SISTEMA DE INVESTIMENTOS";
	mvprintw(1,(coluna - strlen(titulo))/2,titulo);
	refresh();
	box(menu_win,0,0);
	wrefresh(menu_win);
	noecho();
	for(int i=0;i<size ;i++){
		mvwprintw(menu_win,i+2,2,choices[i].c_str());
	}
	wrefresh(menu_win);
}
//----------------------------------------------------------
//-----------------Móulo-Apresentação-Controle--------------
//----------------------------------------------------------
void CntrApresentacaoControle::executar(){
	vector<string> choices={"Acessar Produtos de Investimento","Autenticar Usuario", "Cadastrar Usuario",  "Sair"};
	vector<string> choices_autenticado={"Servicos de Pessoal","Servicos relacionados a Produtos Financeiros","Encerrar Sesao"};
	bool autenticado;
	int linha,coluna;
    getmaxyx(stdscr,linha,coluna);
	while(1){
		clear();
		int escolha=invoca_menu(choices);
		if(escolha==3)
			break;
		if(escolha==0)
			cntrApresentacaoProdutosFinanceiros->executar();
		if(escolha==1){
			if(cntrApresentacaoAutenticacao->autenticar(&cpf)){
				autenticado=true;

				while(autenticado){
					int escolha_usuario=invoca_menu(choices_autenticado);
					if(escolha_usuario==0)
						if(!cntrApresentacaoPessoal->executar(cpf))
							autenticado=false;
					if(escolha_usuario==1)
						cntrApresentacaoProdutosFinanceiros->executar(cpf);
					if(escolha_usuario==2)
						autenticado=false;
				}
			}
			else{
				attron(A_REVERSE);
				mvprintw(linha-2,0,"CPF ou senha incorretos");
				attroff(A_REVERSE);
				mvprintw(linha-1,0,"Pressione qualquer tecla para continuar.");
				getch();
				
			}
		}
		if(escolha==2)
			cntrApresentacaoPessoal->cadastrar();

	}
}
//----------------------------------------------------------
//-----------------Móulo-Apresentação-Autenticação---------
//----------------------------------------------------------
bool CntrApresentacaoAutenticacao::autenticar(CPF* cpf){
	Senha senha;
	char ans;
	bool autenticar=true;
	int linha, coluna;
    getmaxyx(stdscr,linha,coluna);
	while(autenticar){
		try{
			cpf->set_cpf(invoca_texto(DESC,"CPF:"));
			senha.set_senha(invoca_texto(DESC,"Senha:"));

		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			refresh();
			ans=son();
			if(ans=='y')
				continue;
			else
				return false;
		}
		autenticar=false;
	}
	if( cntr->autenticar(*cpf,senha) ){
		return true;
	}

	return false;

}
//----------------------------------------------------------
//-----------------Móulo-Apresentação-Pessoal---------------
//----------------------------------------------------------
void CntrApresentacaoPessoal::cadastrar(){
	clear();
	Nome nome;
	Endereco endereco;
	CEP cep;
	CPF cpf;
	Senha senha;
	CodigoDeBanco codigoDeBanco;
	CodigoDeAgencia codigoDeAgencia;
	Numero numero;
	Usuario usuario;
	Conta conta;
	char ans;
	int linha,coluna;
    getmaxyx(stdscr,linha,coluna);
	while(true){
		try{
			nome.set_nome(invoca_texto(DESC,"Nome:"));
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			refresh();
			ans=son();
			if(ans=='n')
				return;
			else 
				continue;
		}
		break;
	}
	while(true){
		try{
			endereco.set_endereco(invoca_texto(DESC,"Endereco:"));
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			refresh();
			ans=son();
			if(ans=='n')
				return;
			else 
				continue;
		}
		break;
	}
	while(true){
		try{
			cep.set_valor(stoi(invoca_texto(DESC,"CEP:")));
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			refresh();
			ans=son();
			if(ans=='n')
				return;
			else 
				continue;
		}
		break;
	}
	while(true){
		try{
			cpf.set_cpf(invoca_texto(DESC,"CPF:"));
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			refresh();
			ans=son();
			if(ans=='n')
				return;
			else 
				continue;
		}
		break;
	}
	while(true){
		try{
			senha.set_senha(invoca_texto(DESC,"Senha:"));
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			refresh();
			ans=son();
			if(ans=='n')
				return;
			else 
				continue;
		}
		break;
	}
	while(true){
		try{
			codigoDeBanco.set_codigo(invoca_texto(DESC,"Codigo de Banco:"));
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			refresh();
			ans=son();
			if(ans=='n')
				return;
			else 
				continue;
		}
		break;
	}
	while(true){
		try{
			codigoDeAgencia.set_codigo(invoca_texto(DESC,"Codigo de Agencia:"));
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			refresh();
			ans=son();
			if(ans=='n')
				return;
			else 
				continue;
		}
		break;
	}

	while(true){
		try{
			numero.set_numero(invoca_texto(DESC,"Numero da Conta:"));
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			ans=son();
			if(ans=='n')
				return;
			else 
				continue;
		}
		break;
	}

	usuario.set_nome(nome);
	usuario.set_endereco(endereco);
	usuario.set_cep(cep);
	usuario.set_cpf(cpf);
	usuario.set_senha(senha);
	conta.set_agencia(codigoDeAgencia);
	conta.set_banco(codigoDeBanco);
	conta.set_numero(numero);

	attron(A_REVERSE);

	if(cntrServicoPessoal->cadastrar_usuario(usuario,numero)&&
	   cntrServicoProdutosFinanceiros->cadastrar_conta(conta))
		mvprintw(linha-2,0,"Cadastro realizado com sucesso.");
	else
		mvprintw(linha-2,0,"Falha na realizacao do cadastro. Tente novamente.");

	attroff(A_REVERSE);
	mvprintw(linha-1,0,"Pressione qualquer tecla para continuar.");
	getch();

}
	bool CntrApresentacaoPessoal::executar(CPF cpf){
	vector<string> choices={"Apresentar Dados Pessoais","Descadastrar Usuario","Retornar"};
	bool executa=true;
	bool cadastrado=true;
	while(executa){
		int choice=invoca_menu(choices);
		if(choice==0){
			consulta_dados(cpf);
		}
		else if(choice==1)
		{
			descadastrar(cpf);
			cadastrado=executa=false;
		}
		else
			executa=false;
	}
	return cadastrado;
}
void CntrApresentacaoPessoal::consulta_dados(CPF cpf){
	Usuario usuario;
	int linha,coluna;
    getmaxyx(stdscr,linha,coluna);
	vector<string>choices={"Nome    : ","Endereco: ","CEP     : ","CPF     : "};

	if(!cntrServicoPessoal->consultar_usuario(&usuario,cpf))
		return;
	choices[0]+=usuario.get_nome().get_nome();
	choices[1]+=usuario.get_endereco().get_endereco();
	choices[2]+=to_string(usuario.get_cep().get_valor());
	choices[3]+=usuario.get_cpf().get_cpf();

	mostra_atributos(choices);
	mvprintw(linha-1,0,"Pressione qualquer tecla para continuar.");
	getch();
	
}
void CntrApresentacaoPessoal::descadastrar(CPF cpf){
	int linha,coluna;
    getmaxyx(stdscr,linha,coluna);
	clear();
	char titulo[]="SISTEMA DE INVESTIMENTOS";
	mvprintw(1,(coluna - strlen(titulo))/2,titulo);
	attron(A_REVERSE);
	if(cntrServicoProdutosFinanceiros->descadastrar_conta(cpf)&&
		cntrServicoPessoal->descadastrar_usuario(cpf))
		mvprintw(linha-2,0,"Descadastramento realizado com sucesso.");
	else
		mvprintw(linha-2,0,"Falha no descadastramento. Tente novamente.");

	attroff(A_REVERSE);
	mvprintw(linha-1,0,"Pressione qualquer tecla para continuar.");
	refresh();
	getch();

}
//----------------------------------------------------------
//----------Móulo-Apresentação-Produtos-Financeiros---------
//----------------------------------------------------------
void CntrApresentacaoProdutosFinanceiros::listar_produtos(string classe){
	vector<Produto> produtos;
	int linha, coluna,contador =1;
    getmaxyx(stdscr,linha,coluna);
	if(!cntrServicoProdutosFinanceiros->consultar_produtos(produtos, classe)){
		clear();
		char titulo[]="SISTEMA DE INVESTIMENTOS";
		mvprintw(1,(coluna - strlen(titulo))/2,titulo);

		attron(A_REVERSE);
		mvprintw(linha-2,0,"Ainda nao foram cadastrados produtos desta classe");
		attroff(A_REVERSE);
		mvprintw(linha-1,0,"Pressione qualquer tecla para continuar.");
		refresh();
		getch();
		return;
	}
	int size= produtos.size();
	while(produtos.size()){
		vector<string>atributos={
			"Codigo                        : ",
			"Classe                        : ",
			"Emissor                       : ",
			"Prazo (meses)                 : ",
			"Vencimento                    : ",
			"Taxa (%% ao ano)               : ",
			"Horario Limite para Aplicacao : ",
			"Valor Minimo (R$)             : "
		};
		Produto produto=produtos.back();
		atributos[0]+=produto.get_codigo().get_codigo();
		atributos[1]+=produto.get_classe().get_classe();
		atributos[2]+=produto.get_emissor().get_emissor();
		atributos[3]+=to_string( produto.get_prazo().get_prazo() );
		atributos[4]+=produto.get_vencimento().get_data();
		atributos[5]+=to_string( produto.get_taxa().get_taxa() );
		atributos[6]+=produto.get_horario().get_horario();
		atributos[7]+=to_string( produto.get_valor().get_valor() );
		mostra_atributos(atributos);
		mvprintw(linha-1,0,"Pressione qualquer tecla para continuar.");
		attron(A_REVERSE);
		mvprintw(linha-1,coluna-5,"%d/%d",contador,size);
		attroff(A_REVERSE);
		refresh();
		getch();
		contador++;
		produtos.pop_back();

	}

}
void CntrApresentacaoProdutosFinanceiros::selecionar_produtos(){
	bool consulta=true;
	vector<string> choices={"CDB","LCA","LCI","LF","LC","Retornar"};
	while(consulta){
		int choice=invoca_menu(choices);
		if(choice==5)
			break;
		listar_produtos(choices[choice]);
		
	}
}
void CntrApresentacaoProdutosFinanceiros::executar(){
	selecionar_produtos();
}
void CntrApresentacaoProdutosFinanceiros::executar(CPF cpf){
	bool executa=true;
	vector<string> choices={"Acessar Produtos de Investimento","Consultar Conta Corrente","Cadastrar Produto de Investimento","Descadastrar Produto de Investimento","Realizar Aplicacao em Produto de Investimento","Listar Aplicacao em Produtos de Investimento","Retornar"};
	while(executa){
		int choice=invoca_menu(choices);
		if(choice==0)
			selecionar_produtos();
		if(choice==1)
			consulta_conta(cpf);
		if(choice==2)
			cadastra_produto(cpf);
		if(choice==3)
			descadastra_produto(cpf);
		if(choice==4)
			realizar_aplicacao(cpf);
		if(choice==5)
			listar_aplicacoes(cpf);
		if(choice==6)
			executa=false;
	}
}

void CntrApresentacaoProdutosFinanceiros::consulta_conta(CPF cpf){
	int linha,coluna;
    getmaxyx(stdscr,linha,coluna);
	Conta* conta=new Conta();

	vector<string>choices={
		"Banco   : ",
		"Agencia : ",
		"Numero  : "};

	if(!cntrServicoProdutosFinanceiros->consultar_conta(conta,cpf))
		return;
	choices[0]+=conta->get_banco().get_codigo();
	choices[1]+=conta->get_agencia().get_codigo();
	choices[2]+=conta->get_numero().get_numero();

	mostra_atributos(choices);
	mvprintw(linha-1,0,"Pressione qualquer tecla para continuar.");
	getch();
}
void CntrApresentacaoProdutosFinanceiros::cadastra_produto(CPF cpf){
	clear();
	CodigoDeProduto codigo;
	Classe classe;
	Emissor emissor;
	Prazo prazo;
	Data data;
	Taxa taxa;
	Horario horario;
	ValorMinimo valorMinimo;
	Produto produto;
	int linha,coluna;
    getmaxyx(stdscr,linha,coluna);
	bool cadastrar=true;
	char ans;
	while(cadastrar){
		try{
			codigo.set_codigo(invoca_texto(DESC,"Codigo de Produto:"));
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			ans=son();
			if(ans=='n')
				return;
			else
				continue;
		}
		break;
	}
	while(cadastrar){
		try{
			classe.set_classe(invoca_texto(DESC,"Classe:"));
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			ans=son();
			if(ans=='n')
				return;
			else
				continue;
		}
		break;
	}
	while(cadastrar){
		try{
			emissor.set_emissor(invoca_texto(DESC,"Emissor:"));
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			ans=son();
			if(ans=='n')
				return;
			else
				continue;
		}
		break;
	}
	while(cadastrar){
		try{
			prazo.set_prazo(stoi(invoca_texto(DESC,"Prazo de Aplicacao (em meses):")));
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			ans=son();
			if(ans=='n')
				return;
			else
				continue;
		}
		break;
	}
	while(cadastrar){
		try{
			data.set_data(invoca_texto(DESC,"Data de Vencimento:"));
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			ans=son();
			if(ans=='n')
				return;
			else
				continue;
		}
		break;
	}
	while(cadastrar){
		try{
			taxa.set_taxa(stoi(invoca_texto(DESC,"Taxa de Remuneracao (%% ao ano):")));
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			ans=son();
			if(ans=='n')
				return;
			else
				continue;
		}
		break;
	}
	while(cadastrar){
		try{
			horario.set_horario(invoca_texto(DESC,"Horario Limite para Aplicacao:"));
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			ans=son();
			if(ans=='n')
				return;
			else
				continue;
		}
		break;
	}
	while(cadastrar){
		try{
			valorMinimo.set_valor(stoi(invoca_texto(DESC,"Valor Minimo para Aplicacao (reais):")));
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			ans=son();
			if(ans=='n')
				return;
			else
				continue;
		}
		break;
	}
	produto.set_classe(classe);
	produto.set_codigo(codigo);
	produto.set_emissor(emissor);
	produto.set_horario(horario);
	produto.set_prazo(prazo);
	produto.set_taxa(taxa);
	produto.set_vencimento(data);
	produto.set_valor(valorMinimo);

	attron(A_REVERSE);
	if(cntrServicoProdutosFinanceiros->cadastrar_produto(produto,cpf))
		mvprintw(linha-2,0,"Cadastro realizado com sucesso.");
	else
		mvprintw(linha-2,0,"Falha na realizacao do cadastro. Tente novamente.");
	attroff(A_REVERSE);
	mvprintw(linha-1,0,"Pressione qualquer tecla para continuar.");
	getch();
}
void CntrApresentacaoProdutosFinanceiros::descadastra_produto(CPF cpf){
	CodigoDeProduto codigo;
	char ans;
	int linha,coluna;
    getmaxyx(stdscr,linha,coluna);
	while(true){
		try{
			codigo=invoca_texto("Digite o codigo do produto a ser descadastrado:","Codigo de Produto:");
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			ans=son();
			if(ans=='n')
				return;
			else
				continue;
		}
		break;
	}
	attron(A_REVERSE);
	if(cntrServicoProdutosFinanceiros->descadastrar_produto(codigo,cpf))
		mvprintw(linha-2,0,"Descadastramento realizado com sucesso.");
	else
		mvprintw(linha-3,0,"Falha no descadastramento. O produto nao foi encontrado ou nao pode ser descadastrado pelo usuario.");

	attroff(A_REVERSE);
	mvprintw(linha-1,0,"Pressione qualquer tecla para continuar.");
	getch();
	
}
void CntrApresentacaoProdutosFinanceiros::realizar_aplicacao(CPF cpf){
	CodigoDeAplicacao codigoAplicacao;
	CodigoDeProduto codigoProduto;
	ValorDeAplicacao valor;
	Data data;
	Aplicacao aplicacao;
	char ans;
	int linha,coluna;
    getmaxyx(stdscr,linha,coluna);
	while(true){
		try{
			codigoAplicacao.set_codigo( invoca_texto(DESC,"Codigo da Aplicacao:"));
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			refresh();
			ans=son();
			if(ans=='n')
				return;
			else 
				continue;
		}
		break;
	}
	while(true){
		try{
			codigoProduto.set_codigo( invoca_texto(DESC,"Codigo do Produto:"));
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			refresh();
			ans=son();
			if(ans=='n')
				return;
			else 
				continue;
		}
		break;
	}
	while(true){
		try{
			valor.set_valor( invoca_texto(DESC,"Valor da Aplicacao:"));
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			refresh();
			ans=son();
			if(ans=='n')
				return;
			else 
				continue;
		}
		break;
	}
	while(true){
		try{
			data.set_data(invoca_texto(DESC,"Data da Aplicacao:"));
		}
		catch(invalid_argument &exp){
			mvprintw(linha-2,0,AVISO);
			refresh();
			ans=son();
			if(ans=='n')
				return;
			else 
				continue;
		}
		break;
	}
	aplicacao.set_codigo(codigoAplicacao);
	aplicacao.set_valor(valor);
	aplicacao.set_data(data);
	attron(A_REVERSE);
	int resultado=cntrServicoProdutosFinanceiros->realizar_aplicacao(aplicacao,cpf,codigoProduto);
	if(resultado==0)
		mvprintw(linha-2,0,"Aplicacao realizada com sucesso.");
	else if(resultado==1)
		mvprintw(linha-3,0,"Falha na realizacao da aplicacao. Valor fornecido abaixo do valor minimo para aplicacao neste produto.");

	else if(resultado==2)
		mvprintw(linha-3,0,"Falha na realizacao da aplicacao. Produto nao encontrado.");

	else if(resultado==3)
		mvprintw(linha-3,0,"Falha na realizacao da aplicacao.Codigo de aplicacao fornecido ja existe.");

	else if(resultado==4)
		mvprintw(linha-3,0,"Falha na realizacao da aplicacao. O usuario ja atingiu o numero maximo de 5 aplicacoes.");
	else 
		mvprintw(linha-3,0,"Falha na realizacao da aplicacao.Tente novamente.");

	attroff(A_REVERSE);
	mvprintw(linha-1,0,"Pressione qualquer tecla para continuar.");
	getch();

}
void CntrApresentacaoProdutosFinanceiros::listar_aplicacoes(CPF cpf){
	int linha, coluna,contador =1;
    getmaxyx(stdscr,linha,coluna);
	vector<Aplicacao> aplicacoes;
	vector<CodigoDeProduto> codigosDeProduto;
	if(!cntrServicoProdutosFinanceiros->recuperar_aplicacoes(aplicacoes,codigosDeProduto, cpf))
	{
		clear();
		char titulo[]="SISTEMA DE INVESTIMENTOS";
		mvprintw(1,(coluna - strlen(titulo))/2,titulo);

		attron(A_REVERSE);
		mvprintw(linha-2,0,"Ainda nao foram cadastrados produtos desta classe");
		attroff(A_REVERSE);
		mvprintw(linha-1,0,"Pressione qualquer tecla para continuar.");
		refresh();
		getch();
		return;
	}
	int size=aplicacoes.size();
	while(aplicacoes.size()){
		vector<string>atributos={
			"Codigo de Aplicacao : ",
			"Codigo de Produto   : ",
			"Valor (R$)          : ",
			"Data                : "
		};
		Aplicacao aplicacao = aplicacoes.back();
		CodigoDeProduto codigoDeProduto=codigosDeProduto.back();
		atributos[0]+=aplicacao.get_codigo().get_codigo();
		atributos[1]+=codigoDeProduto.get_codigo();
		atributos[2]+=aplicacao.get_valor().get_valor();
		atributos[3]+=aplicacao.get_data().get_data();

		mostra_atributos(atributos);
		mvprintw(linha-1,0,"Pressione qualquer tecla para continuar.");
		attron(A_REVERSE);
		mvprintw(linha-1,coluna-5,"%d/%d",contador,size);
		attroff(A_REVERSE);
		refresh();
		getch();
		contador++;
		aplicacoes.pop_back();
		codigosDeProduto.pop_back();
	}
}



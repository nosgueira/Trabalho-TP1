#include "dominios.h"
#include <bits/stdc++.h>
#include <cctype>

using namespace std;

vector<string> split(string str){

    vector<string> palavras;
    std::size_t current, previous =0;
    current=str.find(" ");
    while(current != string::npos){
        palavras.push_back(str.substr(previous,current-previous));
        previous=current+1;
        current=str.find_first_of(" ",previous);
    }
    if(previous<str.length())
        palavras.push_back(str.substr(previous,current-previous));
    return palavras;
}
//----------------------------------------------------------
//-------------------------CEP------------------------------
//----------------------------------------------------------
const vector<pair<int,int>> CEP::REGIOES  = {
            make_pair(1000000,5999999),
            make_pair(8000000,8499999),
            make_pair(20000000,26600999),
            make_pair(70000000,70999999),
            make_pair(40000000,41999999),
            make_pair(60000000,60999999)};

void CEP::validar(int valor){
    bool valido=false;
    for(pair<int,int> e: REGIOES)
        if(valor>=e.first and valor<=e.second){
            valido=true;
            break;
        }
    if(!valido)
        throw invalid_argument("CEP::validar");
}
CEP::CEP(int valor){
    validar(valor); 
    this->valor=valor;
}

void CEP::set_valor(int valor){
    validar(valor);
    this->valor=valor;
}
//----------------------------------------------------------
//------------------------CLASSE----------------------------
//----------------------------------------------------------
const set<string> Classe::CLASSES_VALIDAS ={"CDB","LCA","LCI","LF","LC"};

void Classe::validar(string nome){
    if(!CLASSES_VALIDAS.count(nome))
        throw invalid_argument("Classe::validar");
}
Classe::Classe(string nome){
    validar(nome);
    this->nome=nome;
}
void Classe::set_classe(string nome){
    validar(nome);
    this->nome=nome;
}
//----------------------------------------------------------
//-------------------CÓDIGO-DE-AGÊNCIA----------------------
//----------------------------------------------------------
const string CodigoDeAgencia::EXCESSAO = "0000";

void CodigoDeAgencia::validar(string codigo){
    if(codigo.length()!=TAMANHO)
        throw invalid_argument("CodigoDeAgencia::validar -> Tamanho Inválido");
    if(codigo==EXCESSAO)
        throw invalid_argument("CodigoDeAgencia::validar -> Argumento Inválido");
    for(char e: codigo)
        if(!isdigit(e))
            throw invalid_argument("CodigoDeAgencia::validar -> Caractere(s) Inválido(s)");
}
CodigoDeAgencia::CodigoDeAgencia(string codigo){
    validar(codigo);
    this->codigo=codigo;
}
void CodigoDeAgencia::set_codigo(string codigo){
    validar(codigo);
    this->codigo=codigo;
}
//----------------------------------------------------------
//------------------CÓDIGO-DE-APLICAÇÃO---------------------
//----------------------------------------------------------

const string CodigoDeAplicacao::EXCESSAO = "00000";

void CodigoDeAplicacao::validar(string codigo){
    if(codigo.length()!=TAMANHO)
        throw invalid_argument("CodigoDeAplicacao::validar -> Tamanho Inválido ");
    if(codigo==EXCESSAO)
        throw invalid_argument("CodigoDeAplicacao::validar -> Argumento Inválido");
    for(char e: codigo)
        if(!isdigit(e))
            throw invalid_argument("CodigoDeAplicacao::validar -> Caractere(s) Inválido(s)");
}
CodigoDeAplicacao::CodigoDeAplicacao(string codigo){
    validar(codigo);
    this->codigo=codigo;
}
void CodigoDeAplicacao::set_codigo(string codigo){
    validar(codigo);
    this->codigo=codigo;
}
//----------------------------------------------------------
//------------------CÓDIGO-DE-BANCO-------------------------
//----------------------------------------------------------

const set<string> CodigoDeBanco::BANCOS={"341","001","237","104","033"};

void CodigoDeBanco::validar(string codigo){
    if(!BANCOS.count(codigo))
        throw invalid_argument("CodigoDeBanco::validar");
}

CodigoDeBanco::CodigoDeBanco(string codigo){
    validar(codigo);
    this->codigo=codigo;

}
void CodigoDeBanco::set_codigo(string codigo){
    validar(codigo);
    this->codigo=codigo;
}
//----------------------------------------------------------
//-------------------CÓDIGO-DE-PRODUTO----------------------
//----------------------------------------------------------

const string CodigoDeProduto::EXCESSAO="000";

void CodigoDeProduto::validar(string codigo){
    if(codigo.length()!=TAMANHO)
        throw invalid_argument("CodigoDeProduto::validar -> Tamanho inválido");
    if(codigo==EXCESSAO)
        throw invalid_argument("CodigoDeProduto::validar -> Argumento inválido");
    for(char e:codigo)
        if(!isdigit(e))
            throw invalid_argument("CodigoDeProduto::validar -> Caractere(s) inválido(s)");
}

CodigoDeProduto::CodigoDeProduto(string codigo){
    validar(codigo);
    this->codigo=codigo;
}

void CodigoDeProduto::set_codigo(string codigo){
    validar(codigo);
    this->codigo=codigo;
}

//----------------------------------------------------------
//------------------------CPF-------------------------------
//----------------------------------------------------------

void CPF::validar(string cpf){
    if(cpf.length()!=TAMANHO)
        throw invalid_argument("CPF::validar -> Tamanho inválido");

    if(!regex_match(cpf,regex("[0-9]{3}\\.[0-9]{3}\\.[0-9]{3}\\-[0-9]{2}")))
        throw invalid_argument("CPF::validar -> Formato inválido");

    vector<int> cpf_numeros, v1, v2;
    bool flag=false;


    for(char e:cpf){
        if(isdigit(e)){
            cpf_numeros.push_back(e -'0');
        }
    }
    for(int i =1; i<(int)cpf_numeros.size();i++){
        if(cpf_numeros[i]!=cpf_numeros[i-1])
        {
            flag=true;
        }
    }
    if(!flag)
        throw invalid_argument("CPF::validar -> CPF inválido");

    for(int i=0, j= 10;j>1;i++,j--){
        v1.push_back(cpf_numeros[i]*j);
    }
    int d1=accumulate(v1.begin(),v1.end(),0)*10;
    d1 %=11;
    if(d1!=cpf_numeros[9])
        throw invalid_argument("CPF::validar -> CPF inválido");


    for(int i=0, j= 11;j>1;i++,j--){
        v2.push_back(cpf_numeros[i]*j);
    }
    int d2=accumulate(v2.begin(),v2.end(),0)*10;
    d2 %=11;
    if(d2!=cpf_numeros[10])
        throw invalid_argument("CPF::validar -> CPF inválido");
}
void CPF::set_cpf(string cpf){
    validar(cpf);
    this->cpf=cpf;
}
//----------------------------------------------------------
//------------------------DATA------------------------------
//----------------------------------------------------------

void Data::validar(string data){

    set<int> trinta {4,6,9,11};
    set<int> trinta_e_um {1,3,5,7,8,10,12};

    if(data.length()!=TAMANHO)
        throw invalid_argument("data::validar -> Formato inválido");
        
    if(!regex_match(data,regex("[0-9]{2}\\/[0-9]{2}\\/[0-9]{4}")))
        throw invalid_argument("data::validar -> Formato inválido");

    int dia = stoi(data.substr(0,2));
    int mes = stoi(data.substr(3,2));
    int ano = stoi(data.substr(6));

    if(mes>12 or mes<1)
        throw invalid_argument("data::validar -> Data inválida");
    if(ano>2099 or ano<2020)
        throw invalid_argument("data::validar -> Data inválida");

    if(trinta.count(mes))
        if(dia>30 or dia<1)
            throw invalid_argument("data::validar -> Data inválida");
    
    if(trinta_e_um.count(mes))
        if(dia>31 or dia<1)
            throw invalid_argument("data::validar -> Data inválida");
    if(mes==2){
        if(!ano%4)
            if(dia>29 or dia<1)
                throw invalid_argument("data::validar -> Data inválida");
        if(ano%4)
            if(dia>28 or dia<1)
                throw invalid_argument("data::validar -> Data inválida");
            
    }

}
Data::Data(){

    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,sizeof(buffer),"%d/%m/%Y",timeinfo);
    string aux(buffer);
    try{
        validar(aux);
        data=aux;
    }
    catch(invalid_argument &e){
        data="01/01/2020";
    }
}

Data::Data(string data){
    validar(data);
    this->data=data;
}

void Data::set_data(string data){
    validar(data);
    this->data=data;
}
//----------------------------------------------------------
//------------------------EMISSOR---------------------------
//----------------------------------------------------------
const set<char> Emissor::VALIDOS={' ','.','-'};

void Emissor::validar(string emissor){

    vector<string> palavras=split(emissor);

    for(int i=1;i<(int)emissor.length();i++){
        if(emissor[i]==' ' and emissor[i-1]==' ')
                    throw invalid_argument("Emissor::validar -> Apenas dígitos e números podem estar em sequência");
            
    }

    if(emissor.length()>TAMANHO_MAX or emissor.length()<TAMANHO_MIN)
        throw invalid_argument("Emissor::validar -> Tamanho inválido");

    for(int i=0;i<(int)emissor.length();i++)
        if((!isalnum(emissor[i]))and(!VALIDOS.count(emissor[i])))
            throw invalid_argument("Emissor::validar -> Caractere inválido");

    for(string e : palavras){
        if(isalpha(e[0]))
            if(islower(e[0]))
                throw invalid_argument("Emissor::validar -> Primeira letra da palavra não é minuscula");

        for(int i=1; i<(int)e.size();i++){
            if((!isalnum(e[i-1])and(!isalnum(e[i]))))
                throw invalid_argument("Emissor::validar -> Apenas dígitos e números podem estar em sequência");
        }
    }
}

void Emissor::set_emissor(string emissor){
    validar(emissor);
    this->emissor=emissor;
}
//----------------------------------------------------------
//------------------------ENDEREÇO--------------------------
//----------------------------------------------------------

const set<char> Endereco::VALIDOS={' ','.'};

void Endereco::validar(string endereco){
    vector<string> palavras =split(endereco);

    for(int i=1;i<(int)endereco.length();i++){
        if(endereco[i]==' ' and endereco[i-1]==' ')
                    throw invalid_argument("Endereco::validar -> Apenas dígitos e números podem estar em sequência");
            
    }
    if(endereco.length()>TAMANHO_MAX or endereco.length()<TAMANHO_MIN)
        throw invalid_argument("Endereco::validar -> Tamanho inválido");

    for(int i=0;i<(int)endereco.length();i++)
        if((!isalnum(endereco[i]))and(!VALIDOS.count(endereco[i])))
            throw invalid_argument("Endereco::validar -> Caractere inválido");

    for(string e : palavras){
        if(isalpha(e[0]))
            if(islower(e[0]))
                throw invalid_argument("Endereco::validar -> Primeira letra da palavra não é minuscula");

        for(int i=1; i<(int)e.size();i++){
            if((!isalnum(e[i-1])and(!isalnum(e[i]))))
                throw invalid_argument("Endereco::validar -> Apenas dígitos e números podem estar em sequência");
        }
    }
}

void Endereco::set_endereco(string endereco){
    validar(endereco);
    this->endereco=endereco;
}

//----------------------------------------------------------
//------------------------HORÁRIO---------------------------
//----------------------------------------------------------

void Horario::validar(string horario){
    
    if(horario.length()!=TAMANHO)
        throw invalid_argument("Horario::validar -> Tamanho inválido");
        
    if(!regex_match(horario,regex("[0-9]{2}\\:[0-9]{2}")))
        throw invalid_argument("Horario::validar -> Formato inválido");

    int horas   = stoi(horario.substr(0,2));
    int minutos = stoi(horario.substr(3));
    if(horas<13 or horas>17 )
        throw invalid_argument("Horario::validar -> Horário inválido");

    if(minutos<0 or minutos>59 )
        throw invalid_argument("Horario::validar -> Horário inválido");
    if(horas==17 and minutos!= 0)
        throw invalid_argument("Horario::validar -> Horário inválido");
}

Horario::Horario(){

    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,sizeof(buffer),"%H:%M",timeinfo);
    string aux(buffer);
    try{
        validar(aux);
        horario=aux;
    }
    catch(invalid_argument &e){
        horario="13:00";
    }
}

Horario::Horario(string horario){
    validar(horario);
    this->horario=horario;
}

void Horario::set_horario(string horario){
    validar(horario);
    this->horario=horario;
}
//----------------------------------------------------------
//------------------------NOME------------------------------
//----------------------------------------------------------

void Nome::validar(string nome){

    
    if(nome.length()>TAMANHO_MAX or nome.length()<TAMANHO_MIN)
        throw invalid_argument("Nome::validar -> Tamanho inválido");

    for(char e : nome)
        if((!isalpha(e)) and e!=' ')
            throw invalid_argument("Nome::validar -> Caractere inválido");
            
    for(int i=1;i<(int)nome.length();i++)
        if(nome[i]==' ' and nome[i-1]==' ')
            throw invalid_argument("Nome::validar -> Não podem haver espaços em sequência");
           
    vector<string> palavras = split(nome);
    if(palavras.size()==1){
        if(palavras[0].length()<5)
            throw invalid_argument("Nome::validar -> Nome deve ter no mínimo 5 caracteres");
    }

    for(string e: palavras)
        if(islower(e[0]))
            throw invalid_argument("Nome::validar -> A primeira letra de cada termo deve ser maiúscula");
}

void Nome::set_nome(string nome){
    validar(nome);
    this->nome=nome;
}


//----------------------------------------------------------
//------------------------NÚMERO----------------------------
//----------------------------------------------------------

int Numero::soma_digitos(int n){
    int soma=0;
    while(n){
        soma+=n%10;
        n/=10;
    }
    return soma;
}
int Numero::aplica_algoritimo(vector<int> digitos){
    int digito_v;
    for(int i=0;i<6;i++){
        if(i%2)
            digitos[i]*=2;
    }
    for(int i=0;i<6;i++){
        digitos[i]=soma_digitos(digitos[i]);
    }

    digito_v=accumulate(digitos.begin(),digitos.end(),0);
    digito_v%=10;
    if(digito_v)
        digito_v=10-digito_v;

    return digito_v;

    
}
void Numero::validar(string numero){
    vector<int> digitos;
    if(numero.length()!=TAMANHO){
        throw invalid_argument("Numero::validar -> Tamanho inválido");
    }
    if(!regex_match(numero,regex("[0-9]{6}\\-[0-9]{1}")))
        throw invalid_argument("Numero::validar -> Formato inválido");

    for(char e : numero){
        if(e=='-')
            break;
        digitos.push_back(e-'0');
    }
    
    if(aplica_algoritimo(digitos)!=(numero[7]-'0'))
        throw invalid_argument("Numero::validar -> Código Inválido ");
    
}

void Numero::set_numero(string numero){
    validar(numero);
    this->numero=numero;
}
//----------------------------------------------------------
//------------------------PRAZO-----------------------------
//----------------------------------------------------------

void Prazo::validar(int prazo){
    if(prazo<6 or prazo>72)
        throw invalid_argument("Prazo::validar");
    if(prazo%6)
        throw invalid_argument("Prazo::validar");
}

Prazo::Prazo(int prazo){
    validar(prazo);
    this->prazo=prazo;
}

void Prazo::set_prazo(int prazo){
    validar(prazo);
    this->prazo=prazo;
}

//----------------------------------------------------------
//------------------------SENHA-----------------------------
//----------------------------------------------------------

void Senha::validar(string senha){
    vector<bool> numeros (10,false);

    if(senha.length()!=TAMANHO)
        throw invalid_argument("Senha::validar -> Tamanho inválido");

    for(char e : senha){
        if(!isdigit(e))
            throw invalid_argument("Senha::validar -> Caracteres devem ser digitos");
        if(numeros[e-'0'])
            throw invalid_argument("Senha::validar -> Digitos devem ser distintos");
        else
            numeros[e-'0']=true;
    }
}


void Senha::set_senha(string senha){
    validar(senha);
    this->senha=senha;
}

//----------------------------------------------------------
//------------------------TAXA------------------------------
//----------------------------------------------------------

void Taxa::validar(int taxa){
    if(taxa>MAX or taxa<MIN)
        throw invalid_argument("Taxa::validar");
}

Taxa::Taxa(int taxa){
    validar(taxa);
    this->taxa=taxa;
}

void Taxa::set_taxa(int taxa){
    validar(taxa);
    this->taxa=taxa;
}

//----------------------------------------------------------
//------------------VALOR-DE-APLICAÇÃO----------------------
//----------------------------------------------------------

void ValorDeAplicacao::validar(string valor){
    auto virgula =valor.find_first_of(",");
    int reais,centavos;
    reais=stoi(valor.substr(0,virgula));
    if(reais>MAX_REAL or reais<MIN_REAL)
        throw invalid_argument("ValorDeAplicacao::validar -> Valor inválido de Reais");

    if(virgula!=string::npos){
        if(virgula<valor.length()-3)
        {
            throw invalid_argument("ValorDeAplicacao::validar -> Podem haver até duas casas após a virgula");
        }
        centavos=stoi(valor.substr(virgula+1));
        if(centavos<MIN_CENT or centavos>MAX_CENT)
            throw invalid_argument("ValorDeAplicacao::validar -> Valor inválido de centavos");
            
        if(reais==MAX_REAL and centavos!=MIN_CENT)
            throw invalid_argument("ValorDeAplicacao::validar -> Valor Acima do permitido");

    }
    
}

void ValorDeAplicacao::set_valor(string valor){
    validar(valor);
    this->valor=valor;
}
//----------------------------------------------------------
//----------------------VALOR-MÍNIMO------------------------
//----------------------------------------------------------
const set<int> ValorMinimo::VALORES_VALIDOS={ 1000, 5000, 10000,50000};

void ValorMinimo::validar(int valor){
    if(!VALORES_VALIDOS.count(valor))
        throw invalid_argument("ValorMinimo::validar");
}

ValorMinimo::ValorMinimo(int valor){
    validar(valor);
    this->valor=valor;
}

void ValorMinimo::set_valor(int valor){
    validar(valor);
    this->valor=valor;
}


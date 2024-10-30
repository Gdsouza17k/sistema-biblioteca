#include <iostream>
#include <cstdio>
#include <limits>
#include <cstring>

using namespace std;

struct emprestimos {
    char dt_emp[10], dt_dev[10], usuario[255];
};

struct livros {
    int codigo, paginas;
    char area[30], titulo[255], autores[255], editora[50];
    struct emprestimos emp;
};

int opc_princ, cod, pos;
char opc;

FILE *arquivo, *arquivoAux;

struct livros livro;

int main(){
    do {
        cout << "=============================" << endl;
        cout << "           MENU              " << endl;
        cout << "=============================" << endl;
        cout << "1 - Cadastro                " << endl;
        cout << "2 - Alteracao               " << endl;
        cout << "3 - Exclusao                " << endl;
        cout << "4 - Emprestimo              " << endl;
        cout << "5 - Devolucao               " << endl;
        cout << "6 - Consulta de livro       " << endl;
        cout << "7 - Livros disponiveis      " << endl;
        cout << "8 - Listagem geral de livros" << endl;
        cout << "9 - Sair                   " << endl;
        cout << "=============================" << endl;
        cout << "Digite a opcao: ";
        cin >> opc_princ;
        cout << "\e[2J" << "\e[0;0H";

        switch (opc_princ){
            case 1:
                cout << "Deseja cadastrar um livro (S ou N)?";
                cin >> opc;
                while (opc == 'S' || opc == 's'){
                    cout << "\e[2J" << "\e[0;0H";
                    cout << "CADASTRANDO LIVRO " << endl << endl;
                    cout << "Codigo: ";
                    cin >> livro.codigo;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Area: ";
                    cin.get(livro.area, 30);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Titulo: ";
                    cin.get(livro.titulo, 255);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Autor(es): ";
                    cin.get(livro.autores, 255);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Editora: ";
                    cin.get(livro.editora, 50);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Numero de paginas: ";
                    cin >> livro.paginas;

                    arquivo = fopen("dados.dat", "ab");
                    if (arquivo == NULL) {
                        arquivo = fopen("dados.dat", "wb");
                    }

                    if (fwrite(&livro, sizeof(struct livros), 1, arquivo) == 1){
                        cout << "Deu tudo certo, livro cadastrado com sucesso!";
                    } else {
                        cout << "Algo deu errado, tente novamente!";
                    }
                    fclose(arquivo);

                    cin.ignore();
                    cin.get();

                    cout << "Deseja cadastrar um novo livro (S ou N)?";
                    cin >> opc;
                    cout << "\e[2J" << "\e[0;0H";
                }
                break;

            case 2:
                arquivo = fopen("dados.dat", "rb+");
                if (arquivo != NULL){

                    cout << "Digite o codigo do livro que deseja alterar: ";
                    cin >> cod;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    pos = -1;
                    while(!feof(arquivo)){
                        fread(&livro, sizeof(struct livros), 1, arquivo);
                        pos++;
                        if (cod == livro.codigo){
                            cout << "\e[2J" << "\e[0;0H";
                            cout << "ALTERANDO LIVRO " << endl << endl;
                            cout << "Area: ";
                            cin.get(livro.area, 30);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Titulo: ";
                            cin.get(livro.titulo, 255);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Autor(es): ";
                            cin.get(livro.autores, 255);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Editora: ";
                            cin.get(livro.editora, 50);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Numero de paginas: ";
                            cin >> livro.paginas;

                            fseek(arquivo, sizeof(struct livros) * pos, SEEK_SET);
                            if (fwrite(&livro, sizeof(struct livros), 1, arquivo) == 1){
                                cout << "Deu tudo certo, livro foi alterado com sucesso!";
                            } else {
                                cout << "Algo deu errado, tente novamente!";
                            } 
                            cin.ignore();
                            cin.get();
                            break;
                        }
                    }
                    fclose(arquivo);

                } else {
                    cout << "Erro ao abrir os dados!";
                    cin.ignore();
                    cin.get();

                }
                cout << "\e[2J" << "\e[0;0H";
                break;
            case 3:
                cout << "Digite o codigo do livro que deseja excluir: ";
                cin >> cod;
                arquivo = fopen("dados.dat", "rb");
                arquivoAux = fopen("dados.aux", "wb");

                fread(&livro, sizeof(struct livros), 1, arquivo);
                while(!feof(arquivo)){
                    if (cod != livro.codigo){
                        fwrite(&livro, sizeof(struct livros), 1, arquivoAux);
                    }
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                }

                fclose(arquivo);
                fclose(arquivoAux);
                remove("dados.dat");
                rename("dados.aux", "dados.dat");
                cout << "Livro excluido com sucesso" << endl;
                cin.ignore();
                cin.get();
                cout << "\e[2J" << "\e[0;0H";
                break;
            case 4:
                arquivo = fopen("dados.dat", "rb+");
                if (arquivo != NULL){
                    cout << "Digite o codigo do livro que deseja emprestar: ";
                    cin >> cod;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    pos = -1;
                    while(!feof(arquivo)){
                        fread(&livro, sizeof(struct livros), 1, arquivo);
                        pos++;
                        if (cod == livro.codigo){
                            fseek(arquivo, sizeof(struct livros) * pos, SEEK_SET);
                            cout << "CONFIGURANDO EMPRESTIMO " << endl << endl;
                            cout << "Data de emprestimo: ";
                            cin.get(livro.emp.dt_emp, 10);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Data de devolucao: ";
                            cin.get(livro.emp.dt_dev, 10);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Usuario: ";
                            cin.get(livro.emp.usuario, 255);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            fwrite(&livro, sizeof(struct livros), 1, arquivo);
                            break;
                        }
                    }
                    fclose(arquivo);

                } else {
                    cout << "Erro ao abrir os dados!";
                    cin.ignore();
                    cin.get();
                }
                cout << "\e[2J" << "\e[0;0H";
                break;
            case 5:
                arquivo = fopen("dados.dat", "rb+");
                if (arquivo != NULL){
                    cout << "Digite o codigo do livro que deseja devolver: ";
                    cin >> cod;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    pos = -1;
                    while(!feof(arquivo)){
                        fread(&livro, sizeof(struct livros), 1, arquivo);
                        pos++;
                        if (cod == livro.codigo){
                            fseek(arquivo, sizeof(struct livros) * pos, SEEK_SET);
                            strcpy(livro.emp.dt_emp, "");
                            strcpy(livro.emp.dt_dev, "");
                            strcpy(livro.emp.usuario, "");
                            fwrite(&livro, sizeof(struct livros), 1, arquivo);
                            break;
                        }
                    }
                    fclose(arquivo);

                } else {
                    cout << "Erro ao abrir os dados!";
                    cin.ignore();
                    cin.get();
                }
                cout << "\e[2J" << "\e[0;0H";
                break;
            case 6:
                arquivo = fopen("dados.dat", "rb");
                if (arquivo != NULL){
                    cout << "Digite o codigo do livro que deseja pesquisar: ";
                    cin >> cod;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    while(!feof(arquivo)){
                        fread(&livro, sizeof(struct livros), 1, arquivo);
                        if (cod == livro.codigo){
                            if (cod == livro.codigo){
                                    cout << "Codigo: " << livro.codigo << endl;
                                    cout << "Area: " << livro.area << endl;
                                    cout << "Titulo: " << livro.titulo << endl;
                                    cout << "Autor(es): " << livro.autores << endl;
                                    cout << "Editora: " << livro.editora << endl;
                                    cout << "Numero de paginas: " << livro.paginas << endl;
                                    cin.get();
                                        
                                break;
                            }
                        }
                    }
                    fclose(arquivo);

                } else {
                    cout << "Erro ao abrir os dados!";
                    cin.ignore();
                    cin.get();
                }
                cout << "\e[2J" << "\e[0;0H";
                break;
            case 7:
                arquivo = fopen("dados.dat", "rb");
                if (arquivo != NULL){
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                    while(!feof(arquivo)){
                        if (strcmp(livro.emp.dt_emp, "") == 0){
                            cout << "Codigo: " << livro.codigo << endl;
                            cout << "Area: " << livro.area << endl;
                            cout << "Titulo: " << livro.titulo << endl;
                            cout << "Autor(es): " << livro.autores << endl;
                            cout << "Editora: " << livro.editora << endl;
                            cout << "Numero de paginas: " << livro.paginas << endl;
                            cout << "---------------------------------------" << endl;
                        }
                        fread(&livro, sizeof(struct livros), 1, arquivo);
                    }
                    fclose(arquivo);
                    cin.ignore();
                    cin.get();
                } else {
                    cout << "Erro ao abrir os dados!";
                    cin.ignore();
                    cin.get();
                }
                break;
                cout << "\e[2J" << "\e[0;0H";
            case 8:
                arquivo = fopen("dados.dat", "rb");
                if (arquivo != NULL){
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                    while(!feof(arquivo)){
                        cout << "Codigo: " << livro.codigo << endl;
                        cout << "Area: " << livro.area << endl;
                        cout << "Titulo: " << livro.titulo << endl;
                        cout << "Autor(es): " << livro.autores << endl;
                        cout << "Editora: " << livro.editora << endl;
                        cout << "Numero de paginas: " << livro.paginas << endl;
                        cout << "---------------------------------------" << endl;
                        fread(&livro, sizeof(struct livros), 1, arquivo);
                    }
                    fclose(arquivo);
                    cin.ignore();
                    cin.get();
                } else {
                    cout << "Erro ao abrir os dados!";
                    cin.ignore();
                    cin.get();
                }
                break;
                cout << "\e[2J" << "\e[0;0H";
            case 9:
                cout << "Obrigado por usar nosso sistema!";
                break;
            default:
                cout << "Opcao invalida, digite novamente! ";
                break;
        }
        cout << "\e[2J" << "\e[0;0H";
    } while (opc_princ != 9);

}
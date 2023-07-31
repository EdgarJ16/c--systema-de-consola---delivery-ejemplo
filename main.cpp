//Proyecto Introducción a la programación
//Entrega de paquetes v2
//Nombre: Edgar Jacob Moreno
//Carne: 117660514
//Domingo 18 de abril

#include<iomanip>
#include<fstream>
#include<iostream>
#include <locale.h>
#include<stdlib.h>
#include<ctime>

using namespace std;
using std::istream;
using std::stringstream;

//PAra transformar string a int
//manipuladores de archivos
ifstream leer;
ofstream guardar;
ofstream temp;
ifstream buscar;


// prototipos de funcion

char menu();//Menu principal
char menu_Chofer(int*);//Abre menu chofer .1
char menu_Clientes(int  *c);//Menu mantenimiento clientes
void agregar_chofer(ofstream &arch_chof,int *id);//Agrega choferes
bool Verifica (int cnslt);//Verifica cedula choferes
bool valStad(int op); // valida status
void agregar_clientes(ofstream &arch_client);//Agrega clientes
bool Verifica_clientes(int Ced);
int valNum(string Tel); //Valida numers
void agregar_pedidos(ofstream &arch_pedidos);//Agrega pedidos al registro
int valPeso(float pes);
int genera_id(void);
bool Verifica_pac(int pac);
bool Verifica_asig(int);//verifica que no se carguen paquetes  a mas de un conductor
bool paquetes_x_camion(ofstream &arch_entrega);

void asigna_pedidos();
//PROGRAMA PRINCIPAL
int main()
{
    setlocale( LC_ALL,"Spanish");
    //Variables

    char op ='0';//menu principal
    char numCed[]="";
    char Nlic[]="";//nueva licencia
    int cedula;
    int id=0;
    bool encontrado=false;//Para busquedas
    string ced,nom,lic,ape,mail,dir;
    string Ndir,Nmail;
    string Ntel,tel;
    int stad;
    int Nstad;//Nuevo estado

    char fecha[]="";
    float peso;
    int monto;
    int id_pack;
    int cedula_envio;
    int cedula_recibe;
    int ganancia;
      int pesoTot;

    //Menu Principal

    while (op != '5')
    {
        system("cls");
        op=menu();

        //Switch principal
        switch(op)
        {
        //Mantenimiento de choferes
        case'1':
            {
                //crea archivo choferes y lo abre
                guardar.open("Choferes.txt",ios::app);


                if(!guardar) //comprueba la apertura del archivo
        {
            cout<<"ERROR AL ABRIR EL ARCHIVO"<<endl;
            exit(1);//Sale del programa
            }
        guardar.close();//cierra archivo una vez creado

        //Sub Menu MANTENIMIENTO CHOFERES .1

        char op_mante_choferes = 'o';//Control para menu .1

                                 cout<<"____MANTENIMIENTO CHOFERES____"<<endl;
                                 cout<<"\n------------------------------------" << endl;
                                 cout<<"Mostrar Lista completa.(1)"<<endl;
                                 cout<<"Buscar/Agregar/Mod.....(2)"<<endl;
                                 cin>>op_mante_choferes;

        if (op_mante_choferes=='1')//Muestra todos los registros de Choferes.txt
        {
            leer.open("Choferes.txt",ios::in);
                leer>>id;//lectura adelantada
                system("cls");
                while (!leer.eof())
                {
                    leer>>cedula;
                    leer>>nom;
                    leer>>ape;
                    leer>>lic;
                    leer>>stad;

                    cout<<"Id       :"<<id<<"\nCedula   :"<<cedula
                        <<"\nNombre   :"<<nom<<"\nApellido :"<<ape<<"\nLicencia :"
                        <<lic<<"\nEstatus  :"<<stad<< "\n_____________"<<endl;

                    leer>>id;//Avanza con el siguiente registro

                }
                system("pause");
                leer.close();


        }//Fin if
        else if (op_mante_choferes=='2')
    {
        cout<<"Ingrese el numero de identificacion del chofer :";
        cin>>(numCed);
            int consulta;

            if (isdigit(numCed[0]))//validacion numerica
            {
                consulta = atoi (numCed);//Convierte char en int
            }
            else
            {
                cout<<"SOLO SE PERMITEN NUMEROS DEBE VOLVER A INICIAR"<<endl;
                system("pause");
            }

            //BUSQUEDA se realiza la busqueda si no esta se agrega
            leer.open("Choferes.txt",ios::in);//Apertura de archivo para busqueda
            leer>>id;//lectura adelantada
            while (!leer.eof())
            {
                leer>>cedula;
                if (cedula == consulta)
                {
                    encontrado=true;
                }
                leer>>nom;
                leer>>ape;
                leer>>lic;
                leer>>stad;
                leer>>id;//avanza al siguiente registro

            }
            leer.close();

            if (!encontrado)
            {
                cout<<"REGISTRO NO ENCONTRADO..."<<endl;
                system("pause");
                agregar_chofer(guardar,&id);
            }
            else
            {
                char opMenu_chofer ='X';
                opMenu_chofer = menu_Chofer(&consulta);
                switch(opMenu_chofer)
                {
                case'1'://Actualiza
                {
                    system("cls");
                    cout<<"ACTUALIZACION DE DATOS\n______________________________________\n"<<endl;
                    cout<<"Cedula :"<<consulta<<endl;
                    cout<<"Actualiza Tipo de licencia..........(1)"<<endl;
                    cout<<"Actualiza Estado del o la choder....(2)\n______________________________________"<<endl;
                    cout<<"opcion ?:";
                    cin>>opMenu_chofer;

                    //Actualiza el tipo de licencia
                    if (opMenu_chofer == '1')
                    {
                        leer.open("Choferes.txt",ios::in);//Apertura de archivo para busqueda
                        temp.open("temp.txt");
                        leer>>id;//lectura adelantada
                        while (!leer.eof())
                        {
                            leer>>cedula;
                            leer>>nom;
                            leer>>ape;
                            leer>>lic;
                            leer>>stad;
                            if (cedula == consulta)
                            {
                                //Se actualiza el dato: Tipo licencia
                                cout<<"Ingrese nuevo tipo de licencia :";
                                cin>>Nlic;
                                temp<<id<<"\n"<<cedula<<"\n"<<nom<<"\n"<<ape<<"\n"<<Nlic<<"\n"<<stad<<endl;


                            }
                            else
                            {
                                temp<<id<<"\n"<<cedula<<"\n"<<nom<<"\n"<<ape<<"\n"<<lic<<"\n"<<stad<<endl;
                            }
                            leer>>id;//avanza al siguiente registro

                        }//fin while
                        leer.close();
                        temp.close();
                        remove ("Choferes.txt");
                        rename ("temp.txt",("Choferes.txt"));
                        break;

                    }//Fin if actualiza

                    //Actualiza estatus del o la chofer

                    else if (opMenu_chofer == '2')
                    {
                        leer.open("Choferes.txt",ios::in);//Apertura de archivo para busqueda
                        temp.open("temp.txt");
                        leer>>id;//lectura adelantada
                        while (!leer.eof())
                        {
                            leer>>cedula;
                            leer>>nom;
                            leer>>ape;
                            leer>>lic;
                            leer>>stad;
                            if (cedula == consulta)
                            {
                                //Se actualiza el dato: Tipo licencia
                                cout<<"Ingrese nuevo estatus |1 = activo | 2 = inactivo| :"<<endl;
                                cout<<"Nuevo Estatus?:";
                                cin>>Nstad;
                                //validacion
                                if (!valStad(Nstad))
                                    {
                                        cout<<"SOLO SE PERMITEN LOS ESTADOS 1(Activo) y 2(Inactivo)"<<endl;
                                        system("pause");
                                        exit(1);
                                    }
                                temp<<id<<"\n"<<cedula<<"\n"<<nom<<"\n"<<ape<<"\n"<<lic<<"\n"<<Nstad<<endl;
                            }
                            else
                            {
                                temp<<id<<"\n"<<cedula<<"\n"<<nom<<"\n"<<ape<<"\n"<<lic<<"\n"<<stad<<endl;
                            }
                            leer>>id;//avanza al siguiente registro

                        }//fin while
                        leer.close();
                        temp.close();
                        remove ("Choferes.txt");
                        rename ("temp.txt",("Choferes.txt"));
                        break;

                    }//Fin else if Estado chofer

                }//Fin case 1

                case'2'://Borra
                {
                    leer.open("Choferes.txt",ios::in);//Apertura de archivo para busqueda
                    temp.open("temp.txt");
                    leer>>id;//lectura adelantada
                    while (!leer.eof())
                    {
                        leer>>cedula;
                        leer>>nom;
                        leer>>ape;
                        leer>>lic;
                        leer>>stad;
                        if (cedula == consulta)
                        {

                            cout<<"Id       :"<<id<<"\nCedula   :"<<consulta
                                <<"\nNombre   :"<<nom<<"\nApellido :"<<ape<<"\nLicencia :"
                                <<lic<<"\nEstatus  :"<<stad<<endl;
                            cout<<"REGISTRO ELIMINADO\n________________________"<<endl;
                            system("pause");

                        }
                        else
                        {
                            temp<<id<<"\n"<<cedula<<"\n"<<nom<<"\n"<<ape<<"\n"<<lic<<"\n"<<stad<<endl;
                        }
                        leer>>id;//avanza al siguiente registro

                    }
                    leer.close();
                    temp.close();
                    remove ("Choferes.txt");
                    rename ("temp.txt",("Choferes.txt"));
                    break;

                }//Fin case 2
                }//fin switch
            } //fin else en caso de que el registro so fuera encontrado
        }//fin else if
        break;
        }//Fin case1 Mantenimiento choferes

        //Mantenimiento de clientes
        case'2':
            {
            //crea archivo clientes y lo abre
            guardar.open("Clientes.txt",ios::app);


            if(!guardar) //comprueba la apertura del archivo
            {
            cout<<"ERROR AL ABRIR EL ARCHIVO"<<endl;
            exit(1);//Sale del programa
            }
            guardar.close();//cierra archivo una vez creado
            //Sub menu Mantenimiento de clientes
            char op_mante_clientes = 'o';//Control para menu .1

                                 cout<<"____MANTENIMIENTO CLIENTES____"<<endl;
                                 cout<<"\n------------------------------------" << endl;
                                 cout<<"Historial de clientes ......(1)"<<endl;
                                 cout<<"Buscar/Agregar/Mod .........(2)"<<endl;
                                 cout<<"SALIR.......................(3)"<<endl;
                                 cout<<"________________________________________"<<endl;
                                 cout<<"Opcion ?:";
                                 cin>>op_mante_clientes;
            switch(op_mante_clientes)
            {
                case'1'://Muestra registro de los clientes
                    {
                        system("cls");
                        cout<<"______CLIENTES_______"<<endl;
                        cout<<"EMITE = 1  |  RECIBE = 2"<<endl;
                        cout<<"_________________________"<<endl;
                        leer.open("Clientes.txt",ios::in);
                        leer>>cedula;//Lectura adelantada
                        while(!leer.eof())
                        {
                            leer>>nom;
                            leer>>ape;
                            leer>>dir;
                            leer>>mail;
                            leer>>tel;
                            leer>>stad;

                    cout<<"\nCedula   :"<<cedula
                        <<"\nNombre   :"<<nom<<"\nApellido :"<<ape<<"\nDireccion:"<<dir
                        <<"\nMail     :"<<mail<<"\nTelefono :"<<tel
                        <<"\nEstatus  :"<<stad
                        << "\n_________________________"<<endl;

                            leer>>cedula;//Continua con el siguiente registro
                        }
                        system("pause");
                        leer.close();
                      break;
                    }//fin case 1 mante clientes Muestra registro
                case'2'://Se pregunta el # de ceduladel cliente y se manipula el registro
                    {
                                encontrado=false;
                                int consulta;
                                system("cls");
                                cout<<"Ingrese el numero de identificación del o la cliente(a)"<<endl;
                                cout<<"Numero de identificación ? :";
                                cin>>(numCed);

                                if (isdigit(numCed[0]))//validacion numerica
                                {
                                    consulta = atoi (numCed);//Convierte char en int
                                }
                                else
                                {
                                    cout<<"SOLO SE PERMITEN NUMEROS DEBE VOLVER A INICIAR"<<endl;
                                    system("pause");
                                }

                               //BUSQUEDA : Se realiza la busqueda en el documento clientes.txt

                                leer.open("Clientes.txt",ios::in);
                                leer>>cedula;//Lectura adelantada
                                while(!leer.eof())
                                {

                                    if (consulta == cedula)
                                    {
                                        encontrado= true;
                                    }
                                    leer>>nom;
                                    leer>>ape;
                                    leer>>dir;
                                    leer>>mail;
                                    leer>>tel;
                                    leer>>stad;
                                    leer>>cedula;//Avanza al siguiente
                                }
                                leer.close();

                                if (!encontrado)
                                {
                                    cout<<"CLIENTE NO REGISTRADO..."<<endl;
                                    system("pause");
                                    system("cls");

                                   agregar_clientes(guardar);
                                }
                                else
                                {
                                    cout<<"CLIENTE REGISTRADO"<<endl;
                                    system("pause");
                                    system("cls");
                                    char opMenu_cliente = menu_Clientes(&consulta);

                                    //BORRAR ACTUALIZAR MODIFICAR
                                    switch(opMenu_cliente)
                                    {
                                    //ACTUALIZACIÓN DE DATOS
                                    case'1':
                                        {
                                            system("cls");
                                                cout<<"ACTUALIZACION DE DATOS\n______________________________________\n"<<endl;
                                                cout<<"Cedula :"<<consulta<<endl;
                                                cout<<"Actualiza Direccion..........(1)"<<endl;
                                                cout<<"Actualiza Telefono...........(2)"<<endl;
                                                cout<<"Actualiza Mail...............(3)"<<endl;
                                                cout<<"\n______________________________________"<<endl;
                                                cout<<"opcion ?:";
                                                cin>>opMenu_cliente;

                            //Actualiza la direccion
                            if (opMenu_cliente == '1')
                            {
                                leer.open("Clientes.txt",ios::in);//Apertura de archivo para busqueda
                                temp.open("temp.txt");
                                leer>>cedula;//lectura adelantada
                                while (!leer.eof())
                                {
                                    leer>>nom;
                                    leer>>ape;
                                    leer>>dir;
                                    leer>>mail;
                                    leer>>tel;
                                    leer>>stad;
                                    if (cedula == consulta)
                                        {
                                            //Se actualiza el dato: direccion
                                            cout<<"Ingrese nueva direccion :";
                                            cin>>Ndir;
                                            temp<<cedula<<"\n"<<nom<<"\n"<<ape<<"\n"<<Ndir<<"\n"<<mail<<"\n"<<tel<<"\n"<<stad<<endl;


                                        }

                                    else
                                        {
                                            temp<<cedula<<"\n"<<nom<<"\n"<<ape<<"\n"<<dir<<"\n"<<mail<<"\n"<<tel<<"\n"<<stad<<endl;
                                        }


                                    leer>>cedula;//avanza al siguiente registro

                                }//fin while
                                leer.close();
                                temp.close();
                                remove ("Clientes.txt");
                                rename ("temp.txt",("Clientes.txt"));

                                }//fin if actualiza direccion

                                 //Actualiza telefono
                            else if (opMenu_cliente == '2')
                            {
                                leer.open("Clientes.txt",ios::in);//Apertura de archivo para busqueda
                                temp.open("temp.txt");
                                leer>>cedula;//lectura adelantada
                                while (!leer.eof())
                                {

                                    leer>>nom;
                                    leer>>ape;
                                    leer>>dir;
                                    leer>>mail;
                                    leer>>tel;
                                    leer>>stad;
                                    if (cedula == consulta)
                                        {
                                            //Se actualiza el dato: telefono
                                            cout<<"Ingrese nueva telefono :";
                                            cin>>Ntel;
                                            temp<<cedula<<"\n"<<nom<<"\n"<<ape<<"\n"<<dir<<"\n"<<mail<<"\n"<<Ntel<<"\n"<<stad<<endl;


                                        }

                                    else
                                        {
                                            temp<<cedula<<"\n"<<nom<<"\n"<<ape<<"\n"<<dir<<"\n"<<mail<<"\n"<<tel<<"\n"<<stad<<endl;
                                        }

                                    leer>>cedula;//avanza al siguiente registro

                                }//fin while
                                leer.close();
                                temp.close();
                                remove ("Clientes.txt");
                                rename ("temp.txt",("Clientes.txt"));

                                }//fin else if actualiza telefono

                                //Actualiza correo
                                else if (opMenu_cliente == '3')
                            {
                                leer.open("Clientes.txt",ios::in);//Apertura de archivo para busqueda
                                temp.open("temp.txt");
                                leer>>cedula;//lectura adelantada
                                while (!leer.eof())
                                {
                                    leer>>nom;
                                    leer>>ape;
                                    leer>>dir;
                                    leer>>mail;
                                    leer>>tel;
                                    leer>>stad;
                                    if (cedula == consulta)
                                        {
                                            //Se actualiza el dato: Mail
                                            cout<<"Ingrese nuevo email :";
                                            cin>>Nmail;
                                            temp<<cedula<<"\n"<<nom<<"\n"<<ape<<"\n"<<dir<<"\n"<<Nmail<<"\n"<<tel<<"\n"<<stad<<endl;


                                        }

                                    else
                                        {
                                            temp<<cedula<<"\n"<<nom<<"\n"<<ape<<"\n"<<dir<<"\n"<<mail<<"\n"<<tel<<"\n"<<stad<<endl;
                                        }


                                    leer>>cedula;//avanza al siguiente registro

                                }//fin while
                                leer.close();
                                temp.close();
                                remove ("Clientes.txt");
                                rename ("temp.txt",("Clientes.txt"));

                                }//fin else if actualiza Mail

                                break;

                                }//Fin case 1 acttualiza datos

                            }//Switch borra actualiza mod

                        }//fin else cliente encontrado

                    }//Fin case 2.2

                }//fin switch menu manteclientes
                break;
            }//fin case 2 Mantenimiento de clientes
        //Envio de paquetes

        case'3':
            {
                 guardar.open("Envios.txt",ios::app);

                if(!guardar) //comprueba la apertura del archivo
                {
                cout<<"ERROR AL ABRIR EL ARCHIVO"<<endl;
                exit(1);//Sale del programa
                }
                int op_pedidos;
                guardar.close();//cierra archivo una vez creado
                cout<<"________ENVIOS______"<<endl;
                cout<<"Nuevo pedido.......(1)"<<endl;
                cout<<"Paquetes en bodega.(2)"<<endl;
                cin>>op_pedidos;

                if (op_pedidos==2)
                {
                    system("cls");
                /*  arch_pedidos
                    cedula_envio
                    cedula_recibe
                    id_pack
                    peso
                    monto
                    dia mes ano*/

                    //muestra los envios en el registro
                    leer.open("Envios.txt",ios::in);
                    leer>>cedula_envio;//Lectura adelantada
                    while(!leer.eof())
                    {
                        leer>>cedula_recibe;
                        leer>>id_pack;
                        leer>>peso;
                        leer>>monto;
                        leer>>fecha;
                        //Muestra el registro
                        cout<<"Cedula recibe:"<<cedula_recibe<<"\nCedula envia"<<cedula_envio<<"\nID paquete:"<<id_pack<<"\nPeso  :"<<peso<<"\nMonto  :"<<monto
                            <<"\nFecha :"<<fecha<<"\n_____________________________\n"<<endl;


                        leer>>cedula_envio;
                    }
                    leer.close();
                    system("pause");
                }
                else if (op_pedidos==1)
                {
                     agregar_pedidos(guardar);
                }
            break;
            }//Fin case 3 envio de paquetes
        //
        case'4':
            {
                cout<<"___CIERRE DE ENVIOS___"<<endl;
                guardar.open("Transporte_Paquetes.txt",ios::out|ios::app);

                if (!guardar)
                {
                    cout<<"ERROR AL ABRIR EL ARCHVIO TRANSPORTE_PAQUETES"<<endl;
                    system("pause");
                    exit(1);
                }
                guardar.close();
                paquetes_x_camion(guardar);



                leer.open("Envios.txt",ios::in);
                    leer>>cedula_envio;//Lectura adelantada
                    while(!leer.eof())
                    {
                        leer>>cedula_recibe;
                        leer>>id_pack;
                        leer>>peso;
                        leer>>monto;
                        leer>>fecha;
                        ganancia += monto;
                        pesoTot+= peso;



                        leer>>cedula_envio;
                    }
                    leer.close();
                     cout<<"TOTAL DE GANANCIA:"<<ganancia<<endl;
                     cout<<"TOTAL PESO CARGADO:"<<pesoTot<<endl;
                     system("pause");









            }//Fin case 4 Envios por paquete

        }//Fin switch

    }//FIN WHILE

}//Fin main

//Funciones
// Valida estatus
bool valStad(int op)
{
    if (op == 1 || op == 2 )
        return true;
    else
        {
        return false;
        }
}

//Verifica repetidos en chofer txt
bool Verifica (int Ced)
{
    int id,ced;
    string nom,ape,lic;
    int stad;
    leer.open("Choferes.txt",ios::in);
    leer>>id;//Lectura adelantada
    while(!leer.eof())
    {
        leer>>ced;
        if (Ced == ced)
        {
            return false;
        }
        leer>>nom;
        leer>>ape;
        leer>>lic;
        leer>>stad;
        leer>>id;
    }
    leer.close();
    return true;

}
//__Agrega chofer
void agregar_chofer(ofstream &arch_chof,int *id)
{
    char resp ='s';
    char numCed[]="";
    string ced;
    string nom;
    string ape;
    string lic;
    int stad;
    int cedula;

    arch_chof.open("Choferes.txt",ios::app);
    while (resp == 'S' || resp == 's')
    {
        ++*id;
        //Identificacion del chofer
        cout<<"\n-------------------------------------------------------------------- "<<endl;
        cout<< "Porfavor ingrese el numero de identificacion del o la chofer :"<<endl;
        cout<<"--------------------------------------------------------------------- "<<endl;
        cout<<"Cedula ?: ";
        cin>>(numCed);
        if (isdigit(numCed[0]))//validacion numerica
        {
            cedula = atoi (numCed);//Convierte char en int
        }
        else
        {
            cout<<"SOLO SE PERMITEN NUMEROS DEBE VOLVER A INICIAR"<<endl;
            remove ("Choferes.txt");
            system("pause");
            exit(1);
        }

        //Nombre del chofer
        cout<<"\n-------------------------------------------------------------------- "<<endl;
        cout<< "Porfavor ingrese el nombre del o la chofer :"<<endl;
        cout<<"--------------------------------------------------------------------- "<<endl;
        cout<<"Nombre ?: ";
        cin>>nom;
        //Apellidos
        cout<<"\n-------------------------------------------------------------------- "<<endl;
        cout<< "Porfavor ingrese el apellido del o la chofer :"<<endl;
        cout<<"--------------------------------------------------------------------- "<<endl;
        cout<<"Apellido ?: ";
        cin>>ape;
        //Tipo de licencia
        cout<<"\n-------------------------------------------------------------------- "<<endl;
        cout<< "Porfavor ingrese el Tipo de licencia "<<endl;
        cout<<"--------------------------------------------------------------------- "<<endl;
        cout<<"Licencia ?: ";
        cin>>lic;
        //Estado
        cout<<"\n-------------------------------------------------------------------- "<<endl;
        cout<< "Porfavor seleccione el estado 1= activo  | 2= inactivo :"<<endl;
        cout<<"--------------------------------------------------------------------- "<<endl;
        cout<<"Estado ?: ";
        cin>>stad;

        if (!valStad(stad))
        {
            cout<<"SOLO SE PERMITEN LOS ESTADOS 1(Activo) y 2(Inactivo)"<<endl;
            system("pause");
            exit(1);
        }


        if(Verifica(cedula))
        {
            arch_chof<<*id<<"\n"<<cedula<<"\n"<<nom<<"\n"<<ape<<"\n"<<lic<<"\n"<<stad<<endl;
        }
        cin.ignore();
        cout<<"DESEA AGREGAR MAS CHOFERES ? S/N"<<endl;
        cin>>resp;
    }//FIN WHILE
    arch_chof.close();
}//Fin agregar chofer

//Agrega clientes
void agregar_clientes(ofstream &arch_client)
{
    char resp ='s';
    char numCed[]=" ";
    char dir[]="";
    string mail;
    string nom;
    string ape;
    string tel;
    int stad;// 1 envia ,2 recibe
    int cedula;

    arch_client.open("Clientes.txt",ios::app|ios::ate);

    while (resp == 'S' || resp == 's')
    {

        //Identificacion del cliente
        cout<<"\n-------------------------------------------------------------------- "<<endl;
        cout<< "Porfavor ingrese el numero de identificacion del o la cliente :"<<endl;
        cout<<"--------------------------------------------------------------------- "<<endl;
        cout<<"Cedula ?: ";
        cin>>(numCed);
        if (isdigit(numCed[0]))//validacion numerica
        {
            cedula = atoi (numCed);//Convierte char en int
        }
        else
        {
            cout<<"SOLO SE PERMITEN NUMEROS DEBE VOLVER A INICIAR"<<endl;
            system("pause");
            exit(1);
        }


        //Nombre del cliente
        cout<<"\n-------------------------------------------------------------------- "<<endl;
        cout<< "Porfavor ingrese el nombre del cliente(a) :"<<endl;
        cout<<"--------------------------------------------------------------------- "<<endl;
        cout<<"nombre cliente(a) ?: ";
        cin>>nom;
        //Apellidos
        cout<<"\n-------------------------------------------------------------------- "<<endl;
        cout<< "Porfavor ingrese el apellido del o la cliente :"<<endl;
        cout<<"--------------------------------------------------------------------- "<<endl;
        cout<<"Apellido ?: ";
        cin>>ape;
        //direccion
        cout<<"\n-------------------------------------------------------------------- "<<endl;
        cout<< "Porfavor ingrese la direccion del cliente(a) :"<<endl;
        cout<<"--------------------------------------------------------------------- "<<endl;
        cout<<"Direccion cliente(a) ?: ";
        cin>>dir;
        //correo
        cout<<"\n-------------------------------------------------------------------- "<<endl;
        cout<< "Porfavor ingrese el correo electronico :"<<endl;
        cout<<"--------------------------------------------------------------------- "<<endl;
        cout<<"Email ?: ";
        cin>>mail;

        //telefono

        cout<<"\n-------------------------------------------------------------------- "<<endl;
        cout<< "Porfavor ingrese el Telefono :"<<endl;
        cout<<"--------------------------------------------------------------------- "<<endl;
        cout<<"Telefono ?: ";
        cin>>tel;

        //Estado emisor(1) /receptor(2)
        cout<<"\n-------------------------------------------------------------------- "<<endl;
        cout<< "Porfavor seleccione el estado | 1= EMISOR  | 2= RECEPTOR :"<<endl;
        cout<<"--------------------------------------------------------------------- "<<endl;
        cout<<"Estado ?: ";
        cin>>stad;

        if (!valStad(stad))
        {
            cout<<"SOLO SE PERMITEN LOS ESTADOS 1(EMISOR) y 2(RECEPTOR)"<<endl;
            system("pause");
            exit(1);
        }
            cout<<"Antes de EL IF :::"<<endl;
            system("pause");


        if(Verifica_clientes(cedula))
        {
            cout<<"ENTRO EN EL IF :::"<<endl;
            system("pause");

            arch_client<<cedula<<"\n"<<nom<<"\n"<<ape<<"\n"<<dir<<"\n"<<mail<<"\n"<<tel<<"\n"<<stad<<endl;
            cout<<"lo guardo en el archivo EN EL IF :::"<<endl;
            system("pause");

        }
        cout<<"SALIO  DEL IF :::"<<endl;
        system("pause");

        cout<<"DESEA AGREGAR MAS CLIENTES ? S/N"<<endl;
        cout<<"opcion ?:";
        cin>>resp;
        cin.ignore();
    }//FIN WHILE
    arch_client.close();
}

//Verifica repetidos en clientes
bool Verifica_clientes(int Ced)
{
    char dir[]="";
    string mail;
    int ced;
    string nom;
    string ape;
    int tel;
    int stad;// 1 envia ,2 recibe
    leer.open("Clientes.txt",ios::in);
    leer>>ced;//Lectura adelantada
    while(!leer.eof())
    {
        if (Ced == ced)
        {
            leer.close();
            return false;
        }
        leer>>nom;
        leer>>ape;
        leer>>dir;
        leer>>mail;
        leer>>tel;
        leer>>stad;
        leer>>ced;
    }
    leer.close();
    return true;

}



//Agrega pedidos
void agregar_pedidos(ofstream &arch_pedidos)
{
                char op = 's';
                char numCed[]="";
                float peso;
                int monto;
                int id_pack;
                int cedula_envio;
                int cedula_recibe;

              //Se abre el archivo para guardar los registros
                arch_pedidos.open("Envios.txt",ios::app);
               while(op=='s' || op=='S')
               {
                   system("cls");

                cout<<"______ENVIO DE PAQUETES_____"<<endl;
                cout<<"   PREPARACION DE PAQUTES"<<endl;
                cout<<"__________________________________\n"<<endl;
                cout<<"Digite la cedula del emisor(a): ";
                cin>>(numCed);
                      //se verifica si la cedula ya existe y si no se agrega

                    if (isdigit(numCed[0]))//validacion numerica
                    {
                        cedula_envio = atoi (numCed);//Convierte char en int
                    }
                    else
                    {
                        cout<<"SOLO SE PERMITEN NUMEROS DEBE VOLVER A INICIAR"<<endl;
                        system("pause");
                        exit(1);
                    }


                if (Verifica_clientes(cedula_envio))
                {
                    cout<<"CLIENTE NO REGISTRADO(A)"<<endl;
                    system("pause");
                    agregar_clientes(guardar);
                    arch_pedidos.open("Envios.txt",ios::app);

                }
                //RECEPTOR RECEPTORA
                cout<<"Digite la cedula del receptor(a):";
                cin>>(numCed);
                if (isdigit(numCed[0]))//validacion numerica
                    {
                        cedula_recibe = atoi (numCed);//Convierte char en int
                    }
                else
                    {
                        cout<<"SOLO SE PERMITEN NUMEROS DEBE VOLVER A INICIAR"<<endl;
                        remove ("Envios.txt");
                        system("pause");
                        exit(1);

                    }

                if (Verifica_clientes(cedula_recibe))
                {
                    cout<<"CLIENTE NO REGISTRADO(A)"<<endl;
                    system("pause");
                    agregar_clientes(guardar);
                    arch_pedidos.open("Envios.txt",ios::app);
                }
                system("cls");
                cout<<"______ENVIO DE PAQUETES_____"<<endl;
                cout<<"   PREPARACION DE PAQUTES"<<endl;
                cout<<"__________________________________\n"<<endl;
                cout<<"Digite el peso del paquete no exceder 1000 kg"<<endl;
                cout<<"Peso? :";
                cin>>peso;
                //Valida el peso
                while (valPeso(peso)!=1)
                {
                    cout<<"Digite el peso correcto:";
                    cin>>peso;
                }
                //calculo del peso
                if (peso<=1)
                {
                    monto=50;

                }
                else if(peso>1)
                {
                    monto = 100 * peso;
                }
                //Asignar fecha y id de registro
                time_t now;
                 struct tm nowLocal; //estructura para asignar con ctime la fecha
                 now = time(NULL);//Info del os
                 nowLocal=*localtime(&now);
                 //año
                 int ano = nowLocal.tm_year+1900;
                 //mes
                 int mes =nowLocal.tm_mon+1;
                 //dia
                 int dia = nowLocal.tm_mday;

                 //ASIGNA ID AL PAQUETE
                 id_pack = genera_id();
                 id_pack++;

                if (!Verifica_pac(id_pack))//Si no se encuentra entonces registra el envio

                {


                    arch_pedidos<<cedula_envio<<"\n"<<cedula_recibe<<"\n"<<id_pack<<"\n"<<peso<<"\n"<<monto<<"\n"<<dia<<"/"<<mes<<"/"<<ano<<endl;
                    cout<<"PEDIDO AÑADIDO AL REGISTRO"<<endl;

                }



                    cout<<"Desea agregar otro pedido ?  S/N :";
                    cin>>op;

               }//fin while principal
   arch_pedidos.close();





}//fin agrega pedidos
//Valida peso
int valPeso(float pes)
{

    if (pes >1000.00 || pes <0)
    {
        cout<<"ERROR limite de peso excedido , su paquete  debe pesar de 0 a 1000.00 kg"<<endl;
        system("pause");
        return 0;
    }
    else
    {
        return 1;
    }

}



//Menu principal
char menu()
{

    system("cls");
    char opMenuP='0';
    cout<<"______PEDRO PAQUETES v.2_______"
        <<"\n------------------------------------" << endl;
    cout<<"->Mantenimiento de choferes..(1)"<<endl;
    cout<<"->Mantenimiento de clientes..(2)"<<endl;
    cout<<"->Envio de paquetes..........(3)"<<endl;
    cout<<"->Cierre de envios...........(4)"<<endl;
    cout<<"->SALIR......................(5)";
    cout<<"\n____________________________________\n" << endl;
    cout<<"Opcion ?:";
    cin>>opMenuP;
    return opMenuP;

}//Fin menu principal
//Menu Chofer
char menu_Chofer(int  *c)
{
    system("cls");
    char opMenuP='0';
    cout<<"____MANTENIMIENTO CHOFERES____"
        <<"\n------------------------------------" << endl;
    cout<<"Numero de identificacion :"<<*c<<endl;
    cout<<"->Actualizar...........(1)"<<endl;
    cout<<"->Borrar...............(2)"<<endl;
    cout<<"->SALIR................(3)";
    cout<<"\n____________________________________\n" << endl;
    cout<<"Mante choferes_opcion?:";
    cin>>opMenuP;
    return opMenuP;

}//Fin menu chofer

//Menu Clientes
char menu_Clientes(int  *c)
{
    system("cls");
    char opMenuP='0';
    cout<<"______MANTENIMIENTO CLIENTES_______"
        <<"\n------------------------------------" << endl;
    cout<<"Numero de identificacion :"<<*c<<endl;
    cout<<"->Actualizar...........(1)"<<endl;
    cout<<"->Borrar...............(2)"<<endl;
    cout<<"->SALIR................(3)";
    cout<<"\n____________________________________\n" << endl;
    cout<<"Mante clientes_opcion?:";
    cin>>opMenuP;
    return opMenuP;
}

//genera id
int genera_id( )
{
    int num;
    srand(time(NULL));
    num = rand();
    return num;

}
//verifica que no se repitan los id de paquetes

bool Verifica_pac(int pac)
{
    int cedula_envio;
    int cedula_recibe;
    int id_pack;
    float peso;
    int monto;
    char fecha[]="";


    leer.open("Envios.txt",ios::in);
    leer>>cedula_envio;//lectura adelantada
    while (!leer.eof())
    {
        leer>>cedula_recibe;
        leer>>id_pack;
        leer>>peso;
        leer>>monto;
        leer>>fecha;
            if (pac == id_pack)
            {
                leer.close();
                return true;// si encuentra un id igual
            }

        leer>>cedula_envio;//Siguiemte registro
    }
leer.close();
return false;
}


bool paquetes_x_camion(ofstream &arch_entrega)
{
    // se asigna  paquetes n:1 chofer mientras no pasen 1000kg




    float suma;

    ifstream extrae;
    //para lectura de envios
        float Lec_peso;
        int Lec_monto;
        int Lec_id_pack;
        int Lec_cedula_envio;
        int Lec_cedula_recibe;
        char Lec_fecha[]="";


    int id_c;
    string nom;
    string ape;
    string lic;
    int stad;
    int cedula;

    // se recoge la info de los choferes
    //Ciclo de operacion principal
    leer.open("Choferes.txt",ios::in);
    arch_entrega.open("Transporte_Paquetes.txt",ios::app|ios::ate);
    temp.open("Temp_Paquetes.txt",ios::out|ios::app);
    extrae.open("Envios.txt",ios::in);
//Reinicio para nueva asignacion de chofer
//CICLO PRONCIPAL DE OPERACION ciclo pricipal extrae choferes y se les asigna un paquete
/* arch_chof<<*id<<"\n"<<cedula<<"\n"<<nom<<"\n"<<ape<<"\n"<<lic<<"\n"<<stad<<endl;*/
leer>>id_c;
while (!leer.eof())
{
    suma=0;
    leer>>cedula;
    leer>>nom;
    leer>>ape;
    leer>>lic;
    leer>>stad;
            if(stad==1) //Entra a estapa de asignacion de paqutes
            {

                        //Se le asignan paquetes hasta que la sumatoria del peso sea menor o igual a 1000kg
                   //EXTRACCION DE DATOS ENVIOS
                  /* arch_pedidos<<cedula_envio<<"\n"<<cedula_recibe<<"\n"<<id_pack<<"\n"<<peso<<"\n"<<monto<<"\n"<<dia<<"/"<<mes<<"/"<<ano<*/

                    extrae>>Lec_cedula_envio;//lectura adelantada
                    while(!extrae.eof())
                        {
                            extrae>>Lec_cedula_recibe;
                            extrae>>Lec_id_pack;
                            extrae>>Lec_peso;
                            extrae>>Lec_monto;
                            extrae>>Lec_fecha;

                            suma+=Lec_peso;



                                if (Verifica_asig(Lec_id_pack) & (suma<=1000))
                                {

                                    arch_entrega<<id_c<<"\n"<<nom<<endl;
                                    arch_entrega<<Lec_peso<<"\n"<<Lec_id_pack<<endl;

                                }

                            temp<<id_c<<"\n"<<nom<<endl;
                            temp<<Lec_peso<<"\n"<<Lec_id_pack<<endl;


                            extrae>>Lec_cedula_envio;//Avanza con el siguiente  registro
                        }
                }


        leer>>id_c;//Continua al siguiente chofer


}//fin while choferes
arch_entrega.close();
leer.close();
extrae.close();
temp.close();
}
//Verifica id de paquetes asignados a algun chofer



bool Verifica_asig(int idX)
{
    int id_c;
    string nom;
    float peso;
    int idPack;

    buscar.open("Temp_Paquetes.txt",ios::in);
    buscar>>id_c;//lectura adelantada
    while (!buscar.eof())
    {
    buscar>>nom;
    buscar>>peso;
    buscar>>idPack;
        if (idPack == idX )
        {
            buscar.close();
            return false;
        }

    buscar>>id_c;
    }

    buscar.close();
    return true;


}







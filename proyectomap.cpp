#include <iostream>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

//estructura
struct TPoint
{
    string nombre;
    string tipo;
    float x;
    float y;
    char estado;
};

//clase 
class CMapa
{
    string nombreArchivo;
    string ciudad;
    map<string, TPoint>lista;
    
public:
    
    //constructores
    CMapa ()
    {
        ciudad = "Lima";
        nombreArchivo = "datos.txt";
    }
    CMapa (string ciudad, string nombre )
    {
        this->ciudad = ciudad;
        this->nombreArchivo = nombreArchivo;
    }
    
    //metodos de procesamiento
    
    //crear el archivo
    void grabarArchivo()
    {
        ofstream archivo(nombreArchivo);
        archivo<<"Nombre, Tipo, Posicion X, Posicion Y, Estado"<<endl;
        for (auto it : lista) 
        {
            auto dato= it.second;
            archivo<<dato.nombre<<", "<<dato.tipo<<", "<<dato.x<<", "<<dato.y<<" ,"<<dato.estado<<endl;
        }
        archivo.close();
    }
    
    //agregar punto (opcion 1)
    void agregar()
    {
        string nombre, tipo;
        float x,y;
        char estado;
        cout<<"Ingrese el nombre del punto: "; cin>>nombre;
        cout<<"Ingrese el tipo de lugar: "; cin>>tipo;
        cout<<"Ingrese el valor de x: "; cin>>x;
        cout<<" Ingrese el valor de y: "; cin>>y;
        cout<<" Ingrese el estado del lugar ( A=abierto, C=cerrado, D=desocupado ): "; cin>>estado;
        lista.insert(pair<string, TPoint>(nombre, {nombre, tipo, x, y, estado}));
        grabarArchivo();
    }
    
    //eliminar punto (opcion 2)
    void eliminar()
    {
        string nombre;
        cout<<"Ingrese el nombre del punto a borrar: "; cin>>nombre;
        lista.erase(nombre);
        grabarArchivo();
    }
    
    //lista de puntos (opcion 3)
    void listar()
    {
        lista.insert(pair<string,TPoint>("UTEC" , {"UTEC","Universidad",20,18,'A'}));
        lista.insert(pair<string,TPoint>("METRO" ,{"METRO","Supermercado",35,8,'A'}));
        lista.insert(pair<string,TPoint>("MIFARMA" ,{"MIFARMA","Farmacia",18,89,'C'}));
        lista.insert(pair<string,TPoint>("PUCP" ,{"PUCP","Universidad",89,64,'C'}));
        lista.insert(pair<string,TPoint>("PETROPERÚ" ,{"PETROPERÚ","Grifo",5,13,'C'}));
        lista.insert(pair<string,TPoint>("FUSEN" ,{"FUSEN","Chifa",33,56,'A'}));
        lista.insert(pair<string,TPoint>("PIURANO" ,{"PIURANO","Restaurant",75,19,'A'}));
        lista.insert(pair<string,TPoint>("RUSTICA" ,{"RUSTICA","Discoteca",36,11,'D'}));
        lista.insert(pair<string,TPoint>("GOUPH" ,{"GOUPH","Bar",77,52,'A'}));
        lista.insert(pair<string,TPoint>("ESTADIO_NACIONAL" ,{"ESTADIO_NACIONAL","Estadio",9,14,'C'}));
        lista.insert(pair<string,TPoint>("HUACHIPA" ,{"HUACHIPA","ZoolÓgico",103,93,'A'}));
        lista.insert(pair<string,TPoint>("BCP" ,{"BCP","Banco",45,15,'A'}));
        lista.insert(pair<string,TPoint>("BBVA" ,{"BBVA","Banco",73,17,'C'}));
        lista.insert(pair<string,TPoint>("HORNERO" ,{"HORNERO","Restaurant",12,35,'D'}));
        for (auto it : lista) 
        {
            auto dato = it.second;
            cout<<"Punto: "<<dato.nombre<<", "<<dato.tipo<<" ("<<dato.x<<", "<<dato.y<<") "<<dato.estado<<endl;
            grabarArchivo();
        }
    }
    
    void listaDePuntosCercanos()
    {
        string nombre;
        cout<<"Ingrese el nombre del lugar: "; cin>>nombre;
        cout<<"La lista de los puntos ubicados a menos de 100 metros son: "<<endl; 
        for (auto it : lista)
        {
            auto dato = it.second;
            if ( nombre==it.first)
            for (auto it1 : lista) 
            {
                auto dato1 = it1.second;
                float d;
                d = sqrt( pow(dato.x-dato1.x,2)+pow(dato.y-dato1.y,2));
                if ( d < 100 && d !=0 )
                cout<<"Punto:" <<dato1.nombre<<", "<<dato1.tipo<<" ("<<dato1.x<<", "<<dato1.y<<") "<<dato1.estado<<endl;
            }
        }
    }
    
    void distanciaPromedioEntrePuntos()
    {
        float total = 0.0;
        float promedio = 0.0;
        for (auto it : lista)
        {
            auto dato = it.second;
            for (auto it1 : lista) 
            {
                auto dato1 = it1.second;
                total+=sqrt( pow(dato.x-dato1.x,2)+pow(dato.y-dato1.y,2));
            }
        }
        int a;
        a=lista.size();
        promedio = total / (a*(a-1));
        cout<< "El distancia promedio entre los puntos es: "<< promedio;
    }
    
   
    
    void mayorDistancia()
    {
        double dmax=0.0;
        for (auto it : lista) 
        {
            auto dato=it.second;
            for (auto it1 : lista) 
            {
                auto dato1=it1.second;
                if(max({pow(dato.x-dato1.x,2)}) && max({pow(dato.y-dato1.y,2)}))
                dmax= max(sqrt( max({pow(dato.x-dato1.x,2)})+ max({pow(dato.y-dato1.y,2)})) ,dmax);
            }
        }
        cout<<"La mayor  distancia es: "<<dmax;
    }
    
    void menorDistancia()
    {
        double dmin=1000;
        for (auto it : lista) 
        {
            auto dato=it.second;
            for (auto it1 : lista) 
            {
                auto dato1=it1.second;
                if(dato.x!=dato1.x && dato.y!=dato1.y)
                dmin= min(sqrt( min({pow(dato.x-dato1.x,2)})+ min({pow(dato.y-dato1.y,2)})),dmin);
            }
        }
        cout<<"La mínima distancia es: "<<dmin;
    }
    
    void tipoDeLugar()
    {
        string tipo;
        cout<<"Ingrese el tipo de lugar: "; cin>>tipo;
        cout<< "La lista de "<<tipo<<"(s)(es)"<<" es : "<<endl;
        for (auto it : lista) 
        {
            auto dato=it.second;
            if( dato.tipo == tipo )
            cout<<"Punto: "<<dato.nombre<<" ("<<dato.x<<", "<<dato.y<<") "<<dato.estado<<endl;
        }
    }
    
    void lugarDeDestino()
    {
        float d=0.0;
        string nombre;
        cout<<"Ingrese el lugar donde se encuentra: "; cin>>nombre;
        string nombre1;
        cout<<"Ingrese el lugar de destino: "; cin>>nombre1;
        for (auto it : lista) 
        {
            auto dato=it.second;
            for (auto it1 : lista) 
            {
                auto dato1=it1.second;
                if ( dato.nombre==nombre && dato1.nombre ==nombre1 )
                d=sqrt( pow(dato.x-dato1.x,2)+pow(dato.y-dato1.y,2));
            }
        }
        cout<<"La distancia al lugar de destino es: "<<d;
    }
    
};

//Se crea el MENÚ
int menu()
{
    int opcion = 0;
    
    do
    {
        system("clear");
        // Saludo
        cout << "¡Bienvenido a TuMapa! Este programa te ayudará a ubicar lugares como restaurantes, cajeros, paraderos y agregar tus lugares preferidos. " << endl;
        cout << "MENÚ" << endl;
        cout << string (4, '-') << endl << endl;
        
        cout << "1. Agregar una nueva posición" << endl;
        cout << "2. Eliminar una posición por nombre" << endl;
        cout << "3. Listar 100 primeros puntos" << endl;
        cout << "4. Listar los puntos ubicados a menos de 10 metros" << endl;               
        cout << "5. Calcular la distancia promedio entre cada punto" << endl;           //entre todos los puntos
        cout << "6. Determinar la distancia entre los puntos más lejanos" << endl;
        cout << "7. Determinar la distancia más corta entre los puntos" << endl;
        cout << "8. Listar tipo de lugar" << endl;
        cout << "9. Distancia entre tu posición y la posición dónde quieres ir" << endl;
        
        cout << "0. Para salir" << endl << endl;
        cout << "Opción: ";
        cin >> opcion;
    } 
    
    while (opcion < 0 || opcion > 9);
    return opcion;
}

int main()
{
    CMapa mapa;         //Mapa de Lima
    int opcion=0;
    
    do
    {
        opcion = menu();        //Opción menu
        
        //Switch de opciones
        switch(opcion)
        {
        case 1:     //Agregar puntos
            system("clear");
            mapa.agregar();
            break;
            
        case 2:     //Eliminar punto
            system("clear");
            mapa.eliminar();
            break;
            
        case 3:     //Lista de puntos
            system("clear");
            mapa.listar();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
          
        case 4:
            system("clear");
            mapa.listaDePuntosCercanos();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
            
        case 5:
            system("clear");
            mapa.distanciaPromedioEntrePuntos();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
            
        case 6:    
            system("clear");
            mapa.mayorDistancia();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
            
        case 7:
            system("clear");
            mapa.menorDistancia();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
            
        case 8:
            system("clear");
            mapa.tipoDeLugar();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        
        case 9:
            system("clear");
            mapa.lugarDeDestino();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        }
    }
    while(opcion!=0);
    
    return 0;
}
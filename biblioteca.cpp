#include <iostream>
#include <vector>

using namespace std;

class Libro;
class Biblioteca;

class Usuario
{   
    private:
        string nombre;
        string direccion;
        int telefono;

    public:
        Usuario(string nombre, string direccion, int telefono)
        {
            this->nombre = nombre;
            this->direccion = direccion;
            this->telefono = telefono;
        }

        void devolverLibro(Libro& lib, Biblioteca& bib);
        friend void prestarLibro(Libro& lib, Biblioteca& biblio);
        friend class Biblioteca;
};

class Libro
{
    private:
        string titulo;
        string autor;

    public:
        Libro(string titulo, string autor)
        {
            this->titulo = titulo;
            this->autor = autor;
        }

        friend class Biblioteca;
        friend void Usuario::devolverLibro(Libro& lib, Biblioteca& bib);
        friend void prestarLibro(Libro& lib, Biblioteca& biblio);

};


class Biblioteca
{
    private:
        vector<Libro>librosDisponibles;
        vector<Libro>librosPrestamo;
        vector<Usuario>usuarios;

    public:

        void buscarLibro(Biblioteca& bib)
        {   
            string buscar= " ";

            cout << "Ingrese el titulo o autor: " ;
            cin >> buscar;

            for (int i=0; i < librosDisponibles.size(); i++)
            {
                if(librosDisponibles[i].titulo == buscar)
                {
                    string opc;
                    string usuario;
                    cout << "Tenemos este libro disponible"<<endl;
                    cout << "Desea solicitar un prestamo? S/N" << endl;
                    cin >> opc;
                    if(opc == "S" || opc == "s")
                    {   
                        prestarLibro(librosDisponibles[i], bib);
                    }
                    return;
                }

                if(librosDisponibles[i].autor == buscar)
                {
                    cout << "Los libros de este autor son:"<<endl;
                    for(int  j=0; j <librosDisponibles.size(); j++)
                    {
                        if(librosDisponibles[j].autor == buscar)
                        {
                            cout << "Titulo: " << librosDisponibles[j].titulo<<endl;
                        }
                    }
                    return;
                }
                
            }
            cout<<"No se encontro el libro"<<endl;
        }

        friend void Usuario::devolverLibro(Libro& lib, Biblioteca& bib);
        friend void prestarLibro(Libro& lib, Biblioteca& biblio);

        void operator-=(const Libro& lib)
        {
            for (int i = 0; i < librosPrestamo.size(); i++)
            {
                if (librosPrestamo[i].titulo == lib.titulo)
                {
                    librosPrestamo.erase(librosPrestamo.begin() + i);
                    break;
                }
            }
        }

        void operator+=(Libro& lib)
        {
            librosPrestamo.push_back(lib);
        }

        void operator-(const Libro& lib)
        {
            for (int i = 0; i < librosDisponibles.size(); i++)
            {
                if (librosDisponibles[i].titulo == lib.titulo)
                {
                    librosDisponibles.erase(librosDisponibles.begin() + i);
                    break;
                }
            }
        }

        void operator+(Libro& lib)
        {
            librosDisponibles.push_back(lib);
        }

        void operator*(Usuario& user)
        {
            usuarios.push_back(user);
        }

};

void Usuario::devolverLibro(Libro& lib, Biblioteca& bib)
{   
    for(int i=0;i<bib.librosPrestamo.size(); i++)
    {
        if(bib.librosPrestamo[i].titulo == lib.titulo)
        {
            bib-=lib;
            bib+lib;
            cout << "Se devolvio:  "<< lib.titulo<<endl;
            return;
        }
    }
    cout << "No se encuentra el libro en la lista de prestamos";
}

void prestarLibro(Libro& x, Biblioteca& biblio)
{   
    string usuario;
    bool encontrado = false, encontradoN = false;
    cout << "Ingrese su nombre: ";
    cin >> usuario;
    for(int i=0;i<biblio.usuarios.size();i++)
    {   
        if(biblio.usuarios[i].nombre==usuario)
        {
            encontradoN = true;
            for(int j=0; j<biblio.librosDisponibles.size(); j++)
            {
                if(biblio.librosDisponibles[j].titulo == x.titulo)
                {
                    encontrado = true;
                    biblio - x;
                    biblio += x;
                    cout << "Se realizo el prestamo de: "<< x.titulo<<endl;
                    break;
                }
            }
            break;
        }
    }

    if(encontrado == false)
        cout <<"No se encontro su nombre en nuestra base de datos"<<endl;
    
    if(encontradoN == false)
        cout <<"El libro no se encuentra disponible"<<endl;
}

int main()
{
    Biblioteca biblioteca;

    Libro libro1("Cien años de soledad", "Gabriel");
    Libro libro2("1984", "George");
    Libro libro3("Don Quijote de la Mancha", "Miguel");

    biblioteca + libro1;
    biblioteca + libro2;
    biblioteca + libro3;

    Usuario usuario("Juan", "Calle 123", 1234567890);
    biblioteca * usuario;

    int opcion;
    bool salir = false;

    while (!salir) {
        cout << "----- MENÚ -----" << endl;
        cout << "1. Buscar libro" << endl;
        cout << "2. Devolver libro" << endl;
        cout << "3. Prestar libro" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        // Limpiar errores y descartar caracteres adicionales
        cin.clear();
        cin.ignore(9999999999999999999, '\n');

        switch (opcion) {
            case 1: {
                biblioteca.buscarLibro(biblioteca);
                break;
            }
            case 2: {
                string titulo;
                cout << "Ingrese el título del libro a devolver: ";
                cin>>titulo;
                Libro libroDevolver(titulo, "");
                usuario.devolverLibro(libroDevolver, biblioteca);
                break;
            }
            case 3: {
                string titulo;
                cout << "Ingrese el título del libro a prestar: ";
                cin>>titulo;
                Libro libroPrestar(titulo, "");
                prestarLibro(libroPrestar, biblioteca);
                break;
            }
            case 4: {
                cout << "Saliendo del programa..." << endl;
                salir = true;
                break;
            }
            default: {
                cout << "Opción inválida. Por favor, ingrese una opción válida." << endl;
                break;
            }
        }
    }

    return 0;
}

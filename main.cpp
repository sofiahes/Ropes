#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>
using namespace std;
class Rope {
private:
    std::string data;
    Rope* left;
    Rope* right;
    int length;

public:
    Rope(const std::string& str = "") : data(str), left(nullptr), right(nullptr), length(str.length()) {}

    // constructor
    Rope(const Rope& other) : data(other.data), left(nullptr), right(nullptr), length(other.length) {
        if (other.left) {
            left = new Rope(*other.left);
        }
        if (other.right) {
            right = new Rope(*other.right);
        }
    }
    
    Rope* getLeft() const {
        return left;
    }

    Rope* getRight() const {
        return right;
    }

    // 
    Rope& operator=(const Rope& other) {
        if (this != &other) {
            delete left;
            delete right;
            left = nullptr;
            right = nullptr;

            data = other.data;
            length = other.length;

            if (other.left) {
                left = new Rope(*other.left);
            }
            if (other.right) {
                right = new Rope(*other.right);
            }
        }
        return *this;
    }

    ~Rope() {
        delete left;
        delete right;
    }

    bool isLeaf() const {
        return left == nullptr && right == nullptr;
    }

    int getLength() const {
        return isLeaf() ? data.length() : length;
    }

    char operator[](int index) const {
        if (isLeaf()) {
            return data[index];
        } else {
            if (index < left->length) {
                return (*left)[index];
            } else {
                return (*right)[index - left->length];
            }
        }
    }

    //uno dos ropes /palabras/caracteres
    void concatenate(const Rope& other) {
        if (isLeaf()) {
            left = new Rope(data);
            right = new Rope(other);
            data = "";
            length += other.length;
        } else {
            right->concatenate(other);
            length += other.length;
        }
    }

    std::string toString() const {
        if (isLeaf()) {
            return data;
        } else {
            return left->toString() + right->toString();
        }
    }
    //divido el rope en dos acorde a un índice
    std::pair<Rope*, Rope*> split(int index) {
    if (index < 0 || index > length) {
        return {nullptr, nullptr};  
    }
    if (index == 0) {
        return {new Rope(""), new Rope(*this)}; //devuelvo el rope original
    } else if (index == length) { //lo mismo de caso 0
        return {new Rope(*this), new Rope("")};

    } else if (isLeaf()) { //si es hoja, lo divido en dos y solo queda un grupo y la hoja
        return {new Rope(data.substr(0, index)), new Rope(data.substr(index))};

    } else { //caso si es nodo interno: divido en dos y actualizo la longitud de cada uno
        if (index <= left->length) {
            auto [leftLeft, leftRight] = left->split(index);
            Rope* resultLeft = leftLeft;
            Rope* resultRight = new Rope(*this);  
            resultRight->left = leftRight; 
            resultRight->length -= resultLeft->length; 
            return {resultLeft, resultRight};
        } else {
            auto [rightLeft, rightRight] = right->split(index - left->length);
            Rope* resultLeft = new Rope(*this);  
            resultLeft->right = rightLeft;  
            resultLeft->length -= rightRight->length;  
            return {resultLeft, rightRight};
        }
    }
}

//Me da la longitud correcta de cada palabra y número del nodo
void updateLength() {
        if (isLeaf()) {
            return;
        }
        left->updateLength();
        right->updateLength();

        length = left->getSubtreeLengthSum();
    }

    // Sum de longitudes de todos los nodos de un subárbol
    int getSubtreeLengthSum() const {
        if (isLeaf()) {
            return data.length();
        } else {
            return left->getSubtreeLengthSum() + right->getSubtreeLengthSum();
        }
    }

    //inserto en el rope
void insert(int index, const std::string& S) {
    if (index < 0) {
        return;  // No se puede insertar en una posición negativa
    }
    if (index==0){
        auto newRope = new Rope(S);
        newRope->concatenate(*this);
        *this = std::move(*newRope);
        delete newRope;
        return;
    }

    if (index > length) {
    
        auto [leftPart, rightPart] = split(length);
        auto newRope = new Rope(S);
        leftPart->concatenate(*newRope);
        *this = std::move(*leftPart);

        delete newRope;
        delete rightPart;
        return;
    }

    auto [leftPart, rightPart] = split(index);
    auto newRope = new Rope(S);
    leftPart->concatenate(*newRope);
    leftPart->concatenate(*rightPart);

    *this = *leftPart;

    delete newRope;
    delete rightPart;

}
//elimino en un index y la cantidad de digitos a eliminar del nodo
void eliminar(int index, int cant) {
    auto [leftPart, rightPart] = split(index);
    auto [leftPart2, rightPart2] = rightPart->split(cant);
    leftPart->concatenate(*rightPart2);
    *this = *leftPart;

    delete leftPart;
    delete rightPart;
    delete leftPart2;
    delete rightPart2;
}

void imprimir(std::ostream& out, unsigned int indent = 0) { //imprimoo
    
    out << std::string(indent, ' ');
    
    if (isLeaf()) {
        out << "|-- " << data << " (" << length << ")\n";
    } else {
        updateLength();
        out << "|-- Node (" << length << ")\n";
        left->imprimir(out, indent + 4);
        right->imprimir(out, indent + 4);
    }
}


bool search(const string& S){ //busco un string en el arbol
    if (isLeaf()) {
        return data == S;
    } else {
        return left->search(S) || right->search(S);
    }
} 
void reverse() { //haré un reverse del rope
        if (isLeaf()) {
            std::reverse(data.begin(), data.end());
        } else {
            left->reverse();
            right->reverse();
            swap(left, right);
        }
}
};

int main() {
    
    const char* s1 = "Habra el curso de"; //HelloLewin, World!!
    const char* s2 = "ADA_EN_VERANO"; 

    //Rope r(s1);

    auto start = std::chrono::system_clock::now();
    
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<float,std::milli> duration = end - start;
    std::cout << duration.count() << "s" << std::endl;
    //getchar();

    //r.insert(6, other);
    //r.insert(7, other);
    Rope r(s1);
    r.insert(5, s2);
    r.insert(13,s2);
    r.insert(15,s1);
    //r.eliminar(3,4);

    // Mostrar el resultado
    std::cout << "Al string: " << r.toString() << std::endl;

    std::cout << "Estructura\n";
    cout<<r.search("win"); //Prueba de busqueda
    cout<<endl;
    r.imprimir(std::cout);
    //r.reverse();
    r.imprimir(std::cout);

    return 0;
}
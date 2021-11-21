#ifndef TP3_TALLER1_COMMON_PACKET_H
#define TP3_TALLER1_COMMON_PACKET_H

#include <string>
#include <vector>

#define PREDEFINED_SIZE_BLOCK 20

/* Clase Packet, representa un paquete que se envia
 * a traves de un socket. Contiene como atributo
 * el array donde guarda, la cantida de bytes enviados,
 * de leidos, y el tamanio del paquete. */
class Packet {
private:
    std::vector<char> array;
    uint32_t sent_;
    uint32_t read_;
    uint32_t size_;

    // Expande el tamanio en otro bloquepredefinido.
    void expand();

    // Expande el tamanio para que entre el tamanio que se pasa.
    void expandUntilMatchSize(const uint32_t &size);

public:
    Packet();

    // Permite agregar bytes al paquete desde un char *.
    void addBytes(char * bytes, const uint32_t & size);

    // Permite agregar bytes al paquete desde un string.
    void addBytes(const std::string & bytes);

    // Permite agregar bytes al paquete desde un uint16_t
    void addBytes(const uint16_t & bytes);

    // Agrega un byte.
    void addByte(char byte);

    // Devuelve un byte.
    char getByte();

    // Devuelve size bytes en forma de string.
    void getBytes(std::string &out, const uint32_t &size);

    void getBytes(uint16_t &out);

    // Suma la cantidad sent a la cantidad de bytes enviados.
    void addSentAmount(const size_t & sent);

    // Devuelve el tamanio que queda por enviar.
    uint32_t pendingToSentSize() const;

    // Devuelve la cantidad de bytes enviados.
    uint32_t sent() const;

    // Devuelve el tamanio del paquete (no del array).
    uint32_t size() const;

    // Devuelve un char pointer a los bytes que quedan por enviar.
    const char * getPendingToSent() const;

    // Resetea el paquete.
    void reset();

    // Resetea el contador de bytes enviados.
    void resetSent();

    void addBytes(const uint8_t &bytes);
};


#endif //TP3_TALLER1_COMMON_PACKET_H

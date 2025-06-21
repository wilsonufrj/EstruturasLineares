#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "Queue.cpp"

class UsuarioBandejao {
 private:
  int id;
  std::string nome;
  int tempoMedioAtendimento;
  std::tm horaEntradaFila;
  int minutosRestantes;

 public:
  UsuarioBandejao(int id, const std::string& nome, int tempoMedio)
      : id(id),
        nome(nome),
        tempoMedioAtendimento(tempoMedio),
        minutosRestantes(0) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    horaEntradaFila = *std::localtime(&now_time);
  }

  void atualizarTempoEspera(int minutos) { minutosRestantes = minutos; }

  std::tm calcularHoraRetirada() const {
    std::tm horaRetirada = horaEntradaFila;
    horaRetirada.tm_min += minutosRestantes;
    mktime(&horaRetirada);
    return horaRetirada;
  }

  void exibirInformacoes() const {
    std::tm hr = calcularHoraRetirada();
    std::cout << "Usuário: " << nome << " | ID: " << id
              << " | Min restantes: " << minutosRestantes
              << " | Hora retirada: " << std::put_time(&hr, "%H:%M")
              << std::endl;
  }

  int getId() const { return id; }
  int getTempoMedio() const { return tempoMedioAtendimento; }
};

template <typename T>
class FilaBandejao : public Queue<T> {
 private:
  int tempoMedioGlobal;

  void atualizarTemposEspera() {
    int tempoAcumulado = 0;
    auto current = this->front.get();

    while (current != nullptr) {
      tempoAcumulado +=
          static_cast<UsuarioBandejao*>(current->data)->getTempoMedio();
      static_cast<UsuarioBandejao*>(current->data)
          ->atualizarTempoEspera(tempoAcumulado);
      current = current->next.get();
    }
  }

 public:
  FilaBandejao(int tempoMedio) : tempoMedioGlobal(tempoMedio) {}

  void enfileirarUsuario(T usuario) {
    Queue<T>::enqueue(usuario);
    atualizarTemposEspera();
  }

  T desenfileirarUsuario() {
    T usuario = Queue<T>::dequeue();
    atualizarTemposEspera();
    return usuario;
  }

  void removerUsuario(int id) {
    std::unique_ptr<typename Queue<T>::Node> temp;
    typename Queue<T>::Node* prev = nullptr;
    typename Queue<T>::Node* current = this->front.get();

    if (current != nullptr &&
        static_cast<UsuarioBandejao*>(current->data)->getId() == id) {
      this->front = std::move(current->next);
      this->size--;
      if (this->isEmpty()) this->rear = nullptr;
      atualizarTemposEspera();
      return;
    }

    while (current != nullptr &&
           static_cast<UsuarioBandejao*>(current->data)->getId() != id) {
      prev = current;
      current = current->next.get();
    }

    if (current == nullptr) {
      throw std::runtime_error("Usuário não encontrado na fila");
    }

    prev->next = std::move(current->next);
    if (current == this->rear) {
      this->rear = prev;
    }
    this->size--;
    atualizarTemposEspera();
  }

  void exibirFila() {
    auto current = this->front.get();
    std::cout << "\n--- Fila do Bandejão ---" << std::endl;
    std::cout << "Tempo médio de atendimento: " << tempoMedioGlobal
              << " minutos" << std::endl;
    std::cout << "Total de pessoas na fila: " << this->size << std::endl;

    while (current != nullptr) {
      static_cast<UsuarioBandejao*>(current->data)->exibirInformacoes();
      current = current->next.get();
    }
    std::cout << "-------------------------" << std::endl;
  }

  void registrarAtraso(int minutos) {
    auto current = this->front.get();
    while (current != nullptr) {
      UsuarioBandejao* usuario = static_cast<UsuarioBandejao*>(current->data);
      usuario->atualizarTempoEspera(usuario->getTempoMedio() + minutos);
      current = current->next.get();
    }
  }

  void registrarAdiantamento(int minutos) {
    if (this->isEmpty()) return;

    this->dequeue();

    auto current = this->front.get();
    while (current != nullptr) {
      UsuarioBandejao* usuario = static_cast<UsuarioBandejao*>(current->data);
      usuario->atualizarTempoEspera(
          std::max(0, usuario->getTempoMedio() - minutos));
      current = current->next.get();
    }
  }
};



#ifndef METHODS_HEADERS_TESTE_H_
#define METHODS_HEADERS_TESTE_H_

// Estrutura para armazenar os parâmetros do controlador PID
typedef struct {
    double kp;  // Ganho proporcional
    double ki;  // Ganho integral
    double kd;  // Ganho derivativo
    double setpoint;  // Valor desejado de referência
    double integral;   // Termo integral acumulado
    double prev_error; // Último erro
} PIDController;



#endif /* METHODS_HEADERS_TESTE_H_ */

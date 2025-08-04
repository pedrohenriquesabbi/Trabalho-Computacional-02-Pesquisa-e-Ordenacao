public class ArvoreBinaria {

    //arvore
    static class No {
        String valor;
        No esquerdo;
        No direito;
        
        
        No(String valor) {
            this.valor = valor;
            this.esquerdo = null;
            this.direito = null;
        }

        No(String valor, No esquerdo, No direito) {
            this.valor = valor;
            this.esquerdo = esquerdo;
            this.direito = direito;
        }

        boolean VerificaOperador() {
            return valor.equals("+") || valor.equals("-") ||
                   valor.equals("*") || valor.equals("/");
        }
    }

    // Operadores
    static int precedencia(String operador) {
        if (operador.equals("+") || 
        operador.equals("-")) return 1;
        
        if (operador.equals("*") || 
        operador.equals("/")) return 2;
        return 0;
    }
 
    
    //função para criar a expressão com parenteses
    static String gerarExpressao(No no) {
        if (no == null) return "";
        // Verifica se é um numero
        if (!no.VerificaOperador()) return no.valor;
        // nos filhos
        String esquerda = gerarExpressao(no.esquerdo);
        String direita = gerarExpressao(no.direito);
        // adiciona parenteses do lado esquerdo
        if (no.esquerdo.VerificaOperador() && precedencia(no.valor) > 
        precedencia(no.esquerdo.valor)) {
            esquerda = "(" + esquerda + ")";
        }
        // Adiciona parenteses do lado direito
        if (no.direito.VerificaOperador() && (
            precedencia(no.valor) > precedencia(no.direito.valor) ||
            (precedencia(no.valor) == precedencia(no.direito.valor) && !no.valor.equals(no.direito.valor))
        )) {
            direita = "(" + direita + ")";
        }
        
        return esquerda + " " + no.valor + " " + direita;
    }
    
    public static void main(String[] args) {
        No arvore1 = new No("+",
            new No("3"),
            new No("*",
                new No("5"),
                new No("8")
            )
        );
        No arvore2 = new No("*",
            new No("+",
                new No("3"),
                new No("5")
            ),
            new No("8")
        );
        System.out.println("Expressao 1: " + gerarExpressao(arvore1));
        System.out.println("Expressao 2: " + gerarExpressao(arvore2));
    }
}













import java.util.Scanner;

public class Banco {
    static Scanner T = new Scanner(System.in);
    static Dados dados = new Dados();
    public static void main(String[] args) {
        boolean stay = true;
        int esc;
        while(stay == true){
            System.out.println("Digite o que você deseja:");
            System.out.println("1-Criar uma conta.");
            System.out.println("2-Saque.");
            System.out.println("3-Depósito.");
            System.out.println("4-Transferência.");
            esc=T.nextInt();
            switch(esc){
                case 1:
                    String nome = cadastro();
                    int id = id();
                    Cliente c = new Cliente(nome,id);
                    dados.setArray(c);
                    System.out.println("Conta criada com sucesso! ID: " + id);
                break;
                case 2:
                    System.out.println("Digite o id da conta:");
                    id=T.nextInt();
                    c=dados.buscar(id);
                    System.out.println("Digite o valor:");
                    double valor = T.nextDouble();
                    c.sacar(valor);
                break;
                case 3:
                    System.out.println("Digite o id da conta:");
                    id=T.nextInt();
                    c=dados.buscar(id);
                    System.out.println("Digite o valor:");
                    valor = T.nextDouble();
                    c.depositar(valor);
                break;
                case 4:
                    Cliente c2 = new Cliente();
                    System.out.println("Digite o id da conta:");
                    id=T.nextInt();
                    c=dados.buscar(id);
                    System.out.println("Digite o id da conta que vais transferir:");
                    id=T.nextInt();
                    c2=dados.buscar(id);
                    System.out.println("Digite o valor:");
                    valor = T.nextDouble();
                    transferencia(valor,c,c2);
                break;
                default:
                System.out.println("Opção inválida");
            }
            System.err.println("Deseja continuar: 1- sim 2- não");
            esc=T.nextInt();
            if(esc == 2){
                stay = false;
            }   
        }         
    }
    public static String cadastro(){
        String nome;
        System.out.println("Digite o nome:");
        nome=T.next();
        return nome;
    }
    public static int id(){
        int id;
        System.out.println("Digite o id:");
        id = T.nextInt();
        return id;
    }
    public static void transferencia(double valor, Cliente c, Cliente c2){
        double valorAntes;
        valorAntes = c.getSaldo();
        c.sacar(valor);
        if (valorAntes == (valor + c.getSaldo())) {
            c2.depositar(valor);    
        }
        
        
    }


}

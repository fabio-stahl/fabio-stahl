public class Cliente {
    private int id;
    private String nome;
    private double saldo;

    public void sacar(double valor){
        if(saldo >= valor)
            saldo = saldo - valor;
    }
    public void depositar(double valor){
        saldo = saldo +valor;
    } 
    public Cliente(){
        
    }
    public Cliente(String nome, int id, double saldo){
        this.nome = nome;
        this.id = id;
        this.saldo = saldo;
    }
    public Cliente(String nome,int id){
        saldo = 0.0;   
        this.nome =nome;
        this.id = id;
    }  

    public void setNome(String nome){
        this.nome = nome;
    }
    public String getNome(){
        return nome;
    }
    public void setId(int id){
        this.id = id;
    }
    public int getId(){
        return id;
    }
    public double getSaldo(){
        return saldo;
    }


}


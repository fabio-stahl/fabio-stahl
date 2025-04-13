import java.util.ArrayList;

public class Dados {
    private ArrayList<Cliente> arrayCliente = new ArrayList<Cliente>();

    public Cliente buscar(int id){
        Cliente c1 = new Cliente();
        for(int i = 0;i < arrayCliente.size();i++){
            c1 = arrayCliente.get(i);
            if(c1.getId() == id){
                return c1;
            }
        }
        return null;
    }
    public void setArray(Cliente p){
        arrayCliente.add(p);
    }

}

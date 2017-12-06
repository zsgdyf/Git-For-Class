package os2;

class Philosopher extends Thread{
    private String name;
    private Fork fork;
    public Philosopher(String name,Fork fork){
        super(name);
        this.name=name;
        this.fork=fork;
    }

    public void run(){
        while(true){
            Thinking();
            fork.TakeFork();
            Eating();
            fork.PutFork();
        }

    }


    public void Eating(){
        System.out.println("EATING:"+name);
        try {
            sleep(500);//模拟吃饭，等待0.5s
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    public void Thinking(){
        System.out.println("THINKING:"+name);
        try {
            sleep(500);//模拟思考，等待0.5s
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}

class Fork{
    //筷子访问位
    private boolean[] used={false,false,false,false,false,false};
    public synchronized void TakeFork(){
        String name = Thread.currentThread().getName();
        int i = Integer.parseInt(name);
        while(used[i]||used[(i+1)%5]){//一旦左右筷子都被占用
            try {
                wait();
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
        used[i]=true;
        used[(i+1)%5]=true;
    }

    public synchronized void PutFork(){
        String name = Thread.currentThread().getName();
        int i = Integer.parseInt(name);
        used[i]= false;
        used[(i+1)%5]=false;
        notifyAll();
    }
}
public class os2 {
    public static void main(String []args){
        Fork fork = new Fork();
        new Philosopher("0",fork).start();
        new Philosopher("1",fork).start();
        new Philosopher("2",fork).start();
        new Philosopher("3",fork).start();
        new Philosopher("4",fork).start();
    }
}

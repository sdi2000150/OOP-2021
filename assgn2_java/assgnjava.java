
import java.util.Random; //for random initialization of the classes

class App {
    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]), reuma = Integer.parseInt(args[1]), katastasi = Integer.parseInt(args[2]); //Parse string args to int
        movement r = movement.values()[reuma]; //select the enum "movement" value in position "reuma" and assign it to "movement" type variable "r"
        condition k = condition.values()[katastasi]; //select the enum "condition" value in position "katastasi" and assign it to "condition" type variable "k"

        artifact[] artifactArray = new artifact[N]; //pinakas apo anafores se artifact megethous N
        Random rand = new Random(); //instance of random class
        int eidos;
        for (int i = 0 ; i < N ; i++) {
            eidos = rand.nextInt(2); //generates random numbers in the range 0 to 1 (0 for creating a painting or 1 for creating a sculpture)
            if (eidos == 0) {
                //lenght and width are between 10.0 and 100.0(randomly generated), technique's,movement's and condition's values are selected randomly(between 0 and 2 positions of each enum), index is i, creator's name is "Creator"+index, year is between 1200 and 2000(randomly generated)
                artifactArray[i] = new painting(rand.nextInt(90)+10,rand.nextInt(90)+10,technique.values()[rand.nextInt(3)],movement.values()[rand.nextInt(3)],condition.values()[rand.nextInt(3)],i,"Creator"+i,rand.nextInt(800)+1200);
            } else {
                //volume is between 1.0 and 10.0(randomly generated), material's,movement's and condition's values are selected randomly(between 0 and 2 positions of each enum), index is i, creator's name is "Creator"+index, year is between 1200 and 2000(randomly generated)
                artifactArray[i] = new sculpture(rand.nextInt(10)+1,material.values()[rand.nextInt(3)],movement.values()[rand.nextInt(3)],condition.values()[rand.nextInt(3)],i,"Creator"+i,rand.nextInt(800)+1200);
            }
        }
        auction(N,artifactArray,r,k); //send the array of artifacts and his size and the values of movement and condition that are given from the command line
    }

    static void auction(int N, artifact[] artifactArray,movement r,condition k) {
        System.out.println("\nArtifacts need to be from "+r+" movement and in "+k+" condition, in order to be accepted");
        for (int i = 0 ; i < N ; i++) {
            System.out.println();
            artifactArray[i].getIndex(); //print the artifact's index
            artifactArray[i].getInfo(); //print the artifact's rest info
            boolean apodekto = artifactArray[i].evaluate(r,k); //call the artifact's function evaluate to determine whether it's acceptable or not
            if (apodekto == true) { //if function evaluate returns true artifact is acceptable
                System.out.println("Artifact is acceptable");
            } else { //else if function evaluate returns false artifact is not acceptable
                System.out.println("Artifact is not acceptable");
            }
        }
    }
}

//abstract because no objects of artifact are being created
abstract class artifact {
    private final int index; //private because no use in subclasses and final because it remains constant
    private final String creator; //private because no use in subclasses and final because it remains constant
    private final int year; //private because no use in subclasses and final because it remains constant

    artifact(int i, String c, int y) {
        index = i;
        creator = c;
        year = y;
        System.out.println("Creating an instance of artifact");
    }

    void getInfo() {
        System.out.println("Artifact's creator is: "+creator+"\nArtifact's creation year is: "+year+" AD");
    }
    void getIndex() {
        System.out.println("Artifact's index is: "+index);
    }

    abstract void setCondition(condition k); //abstract declaration of subclass' masterpiece function setCondition

    //abstract declaration of subclass' painting and sculpture functions evaluate
    abstract boolean evaluate(movement r,condition k);
    abstract boolean evaluate(movement r); 
}

enum movement { //using enum to represent the values movement can get
    impressionism,
    expressionism,
    naturalism
}
enum condition { //using enum to represent the values condition can get
    bad,
    good,
    excellent
}
//abstract because no objects of masterpiece are being created
abstract class masterpiece extends artifact {
    protected final movement reuma; //protected for use in subclasses and final because it remains constant(movement does not change)
    protected condition katastasi; //protected for use in subclasses (not final because condition can change)

    masterpiece(movement r, condition k, int i, String c, int y) {
        super(i,c,y); //call the constructor of superclass artifact
        reuma = r;
        katastasi = k;
        System.out.println(" Creating an instance of masterpiece");
    }

    void getInfo() {
        super.getInfo(); //call function getInfo of superclass artifact
        System.out.println(" Masterpiece's movement is: "+reuma+"\n Masterpiece's condition is: "+katastasi);
    }

    void setCondition(condition k) { //h katastasi mporei na metablhthei anathetontas tin katallhlh timh
        katastasi = k;
    }
}

enum technique { //using enum to represent the values technique can get
    oil,
    aquarelle,
    tempera
}
class painting extends masterpiece {
    private final double lenght; //private because no use in subclasses(none other) and final because it remains constant
    private final double width; //private because no use in subclasses(none other) and final because it remains constant
    private final technique texnikh; //private because no use in subclasses(none other) and final because it remains constant

    painting(double l, double w, technique t, movement r, condition k, int i, String c, int y) {
        super(r,k,i,c,y); //call the constructor of superclass masterpiece
        lenght = l;
        width = w;
        texnikh = t;
        System.out.println("  Creating an instance of painting");
    }

    void getInfo() {
        super.getInfo(); //call function getInfo of superclass masterpiece
        System.out.println("  Painting's length is: "+lenght+" cm\n  Painting's width is: "+width+" cm\n  Painting's technique is: "+texnikh);

        double surface = lenght*width;
        System.out.println("  Painting's surface is: "+surface+" cm^2");
    }

    boolean evaluate(movement r,condition k) {
        //should have equal movement and equal condition(condition could be different if the given one is good and the painting's one is excellent)
        if (reuma == r && (katastasi == k || (katastasi == condition.excellent && k == condition.good))) {
            return true;
        } else {
            return false;
        }
    }
    boolean evaluate(movement r) { //condition = good(in case no condition is given)
        return evaluate(r,condition.good); //just call the other evaluate with condition as good
    }
}

enum material { //using enum to represent the values material can get
    iron,
    stone,
    wood
}
class sculpture extends masterpiece {
    private final double volume; //private because no use in subclasses(none other) and final because it remains constant(volume does not change)
    private final material uliko; //private because no use in subclasses(none other) and final because it remains constant(material does not change)

    sculpture(double v, material u, movement r, condition k, int i, String c, int y) {
        super(r,k,i,c,y); //call the constructor of superclass masterpiece
        volume = v;
        uliko = u;
        System.out.println("  Creating an instance of sculpture");
    }

    void getInfo() {
        super.getInfo(); //call function getInfo of superclass masterpiece
        System.out.println("  Sculpture's volume is: "+volume+" m^3\n  Sculpture's material is: "+uliko);
    }

    boolean evaluate(movement r,condition k) {
        //should have equal movement and equal condition
        if (reuma == r && katastasi == k /*&& !(katastasi == condition.excellent && k == condition.good)*/) {
            return true;
        } else {
            return false;
        }
    }
    boolean evaluate(movement r) { //condition = excellent (in case no condition is given)
        return evaluate(r,condition.excellent); //just call the other evaluate with condition as excellent
    }
}
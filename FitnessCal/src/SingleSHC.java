import java.util.ArrayList;

public class SingleSHC {
	float t = 0.1f;
	float[] destination = { 2.0f, 1.5f, 1.0f };
	int n1 = 1000;

	boolean x_flag = false;
	boolean y_flag = false;
	boolean z_flag = false;

	// 用来存贮走过的路径点,绘图用
	ArrayList<VelocityNotZero> vel1 = new ArrayList<VelocityNotZero>();
	ArrayList<VelocityZero> vel2 = new ArrayList<VelocityZero>();

	public void runNotZero() {
		VelocityNotZero tmp = null; // The final point
		String contents = "";
		float f = 0.0f;

		VelocityNotZero v = new VelocityNotZero();
		v.CalDistance(destination, t);
		v.CalFitness();

		VelocityNotZero v2 = new VelocityNotZero();
		v2.CalDistance(destination, t);
		v2.CalFitness();

		if (v.getFitness() > v2.getFitness()) {
			vel1.add(v);
			v.GenDistance(t);
			tmp = recursionNotZero(v, n1);
		} else {
			vel1.add(v2);
			v2.GenDistance(t);
			tmp = recursionNotZero(v2, n1);
		}

		for (int i = 0; i < vel1.size(); i++) {
			contents += vel1.get(i).toString();
			f += vel1.get(i).getFitness();
		}
		
		System.out.println("Average Fitness(judge zero): " + f/vel1.size());
		new FileOp().writeFile(contents, "dataNotZero.txt", false);
	}

	public void runZero() {
		VelocityZero tmp = null; // The final point
		String contents = "";
		float f = 0.0f;

		VelocityZero v = new VelocityZero();
		v.CalDistance(destination, t);
		v.CalFitness();

		VelocityZero v2 = new VelocityZero();
		v2.CalDistance(destination, t);
		v2.CalFitness();

		if (v.getFitness() > v2.getFitness()) {
			vel2.add(v);
			v.GenDistance(t);
			tmp = recursionZero(v, n1);
		} else {
			vel2.add(v2);
			v2.GenDistance(t);
			tmp = recursionZero(v2, n1);
		}

		for (int i = 0; i < vel2.size(); i++) {
			contents += vel2.get(i).toString();
			f += vel2.get(i).getFitness();
		}
		
		System.out.println("Average Fitness(not judge zero): " + f/vel2.size());
		new FileOp().writeFile(contents, "dataZero.txt", false);
	}

	public VelocityNotZero recursionNotZero(VelocityNotZero v1, int n) {
		VelocityNotZero v2 = new VelocityNotZero();
		v2.UpdateDistance(v1);
		v2.CalDistance(destination, t);
		v2.CalFitness();

		if (v1.getFitness() > v2.getFitness()) {

			if (n > 0) {
				vel1.add(v1);
				return recursionNotZero(v1, n - 1);
			} else {
				return v1;
			}
		} else {
			if (n > 0) {
				vel1.add(v2);
				v2.GenDistance(t);
				return recursionNotZero(v2, n - 1);
			} else {
				return v2;
			}
		}
	}

	public VelocityZero recursionZero(VelocityZero v1, int n) {
		VelocityZero v2 = new VelocityZero();
		v2.UpdateDistance(v1);
		v2.CalDistance(destination, t);
		v2.CalFitness();

		if (v1.getFitness() > v2.getFitness()) {

			if (n > 0) {
				vel2.add(v1);
				return recursionZero(v1, n - 1);
			} else {
				return v1;
			}
		} else {
			if (n > 0) {
				vel2.add(v2);
				v2.GenDistance(t);
				return recursionZero(v2, n - 1);
			} else {
				return v2;
			}
		}
	}

	public void setDestination(float[] destination) {
		this.destination = destination;
	}
}

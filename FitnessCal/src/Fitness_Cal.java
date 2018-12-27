import java.util.ArrayList;

public class Fitness_Cal implements Runnable {
	float t = 0.1f;
	float[] destination = { 2.0f, 1.5f, 1.0f };
	int n1 = 1000;
	int n2 = 5000; // MGA算法的循环次数应与最优SHC解的数量相同

	static boolean x_flag = false;
	static boolean y_flag = false;
	static boolean z_flag = false;
	
	int Dx_count_org = 0;
	int Dy_count_org = 0;
	int Dz_count_org = 0;

	// 用来存贮走过的路径点,绘图用
	ArrayList<VelocityZero> vel = new ArrayList<VelocityZero>();

	public void run() {
		ArrayList<VelocityZero> arr = new ArrayList<VelocityZero>();

		if (destination[0] == 0.0f) {
			x_flag = true;
		}
		if (destination[1] == 0.0f) {
			y_flag = true;
		}
		if (destination[2] == 0.0f) {
			z_flag = true;
		}

		// 最优SHC算法(即循环n2次SHC算法,取fitness最大)
		for (int i = 0; i < n2; i++) {
			VelocityZero v = new VelocityZero();
			v.CalDistance(destination, t);
			v.CalFitness();

			VelocityZero v2 = new VelocityZero();
			v2.CalDistance(destination, t);
			v2.CalFitness();

			if (v.getFitness() > v2.getFitness()) {
				vel.add(v);
				v.GenDistance(t);
				VelocityZero tmp = recursion(v, n1);
				arr.add(tmp);
				// System.out.println("Result:");
				// System.out.println("Fitness: " + tmp.getFitness());
				// System.out.println("Velocity: vx: " + tmp.getVx() + " vy:
				// " +
				// tmp.getVy() + " vz: " + tmp.getVz());
				// System.out.println("Distance: dx: " + tmp.getDx() + " dy:
				// " +
				// tmp.getDy() + " dz: " + tmp.getDz());
			} else {
				vel.add(v2);
				v2.GenDistance(t);
				VelocityZero tmp = recursion(v2, n1);
				arr.add(tmp);
				// System.out.println("Result:");
				// System.out.println("Fitness: " + tmp.getFitness());
				// System.out.println("Velocity: vx: " + tmp.getVx() + " vy:
				// " +
				// tmp.getVy() + " vz: " + tmp.getVz());
				// System.out.println("Distance: dx: " + tmp.getDx() + " dy:
				// " +
				// tmp.getDy() + " dz: " + tmp.getDz());
			}
		}

		for (int x = 0; x < arr.size(); x++) {
			System.out.println(arr.get(x).getDx() + "; " + arr.get(x).getDy() + "; " + arr.get(x).getDz() + "; ");
		}

		System.exit(0);
		// for(int i = 0; i<vel.size(); i++){
		// System.out.println((i + 1) +".Dx: " + vel.get(i).getDx() + ";Dy: " +
		// vel.get(i).getDy() + ";Dz: " + vel.get(i).getDz() + "\r\n");
		// }

		// MGA算法(即将n2个SHC算法的解,随机抽选,判断f值,并交换一个方向的v)
		for (int i = 0; i < n2; i++) {
			int val1 = (int) (Math.random() * n2);
			int val2 = (int) (Math.random() * n2);

			if (arr.get(val1).getFitness() > arr.get(val2).getFitness()) {
				// 如果随机选择到为0的轴,则重新生成随机数
				int which = -1;
				while (true) {
					which = (int) (Math.random() * 3);
					if (x_flag && (which == 0))
						continue;
					if (y_flag && (which == 1))
						continue;
					if (z_flag && (which == 2))
						continue;
					else
						break;
				}

				switch (which) {
				case 0: {
					arr.get(val2).ChangeDistance(which, 0 - arr.get(val2).getVx(), t);
					arr.get(val2).setVx(arr.get(val1).getVx());
					arr.get(val2).ChangeDistance(which, arr.get(val2).getVx(), t);
					arr.get(val2).CalDistance2(destination, t);
					arr.get(val2).CalFitness();
					break;
				}
				case 1: {
					arr.get(val2).ChangeDistance(which, 0 - arr.get(val2).getVy(), t);
					arr.get(val2).setVy(arr.get(val1).getVy());
					arr.get(val2).ChangeDistance(which, arr.get(val2).getVy(), t);
					arr.get(val2).CalDistance2(destination, t);
					arr.get(val2).CalFitness();
					break;
				}
				case 2: {
					arr.get(val2).ChangeDistance(which, 0 - arr.get(val2).getVz(), t);
					arr.get(val2).setVz(arr.get(val1).getVz());
					arr.get(val2).ChangeDistance(which, arr.get(val2).getVz(), t);
					arr.get(val2).CalDistance2(destination, t);
					arr.get(val2).CalFitness();
					break;
				}
				default: {
					break;
				}
				}
			} else if (arr.get(val1).getFitness() < arr.get(val2).getFitness()) {
				int which = (int) (Math.random() * 3);
				switch (which) {
				case 0: {
					arr.get(val1).ChangeDistance(which, 0 - arr.get(val1).getVx(), t);
					arr.get(val1).setVx(arr.get(val2).getVx());
					arr.get(val1).ChangeDistance(which, arr.get(val1).getVx(), t);
					arr.get(val1).CalDistance2(destination, t);
					arr.get(val1).CalFitness();
					break;
				}
				case 1: {
					arr.get(val1).ChangeDistance(which, 0 - arr.get(val1).getVy(), t);
					arr.get(val1).setVy(arr.get(val2).getVy());
					arr.get(val1).ChangeDistance(which, arr.get(val1).getVy(), t);
					arr.get(val1).CalDistance2(destination, t);
					arr.get(val1).CalFitness();
					break;
				}
				case 2: {
					arr.get(val1).ChangeDistance(which, 0 - arr.get(val1).getVz(), t);
					arr.get(val1).setVz(arr.get(val2).getVz());
					arr.get(val1).ChangeDistance(which, arr.get(val1).getVz(), t);
					arr.get(val1).CalDistance2(destination, t);
					arr.get(val1).CalFitness();
					break;
				}
				default: {
					break;
				}
				}
			} else {
				continue;
			}
		}

		VelocityZero result = new VelocityZero();
		result.setFitness(0.0f);

		for (int i = 0; i < arr.size(); i++) {
			if (result.getFitness() >= arr.get(i).getFitness()) {
				;
			} else {
				result = arr.get(i);
			}
		}

		System.out.println("Result:");
		System.out.println("Fitness: " + result.getFitness());
		System.out.println("Velocity: vx: " + result.getVx() + " vy: " + result.getVy() + " vz: " + result.getVz());
		System.out.println("Distance: dx: " + result.getDx() + " dy: " + result.getDy() + " dz: " + result.getDz());

		synchronized (this) {
			new FileOp().writeFile(result.getDx() + "\r\n", "Dx.txt", true);
			new FileOp().writeFile(result.getDy() + "\r\n", "Dy.txt", true);
			new FileOp().writeFile(result.getDz() + "\r\n", "Dz.txt", true);
		}
	}

	public void notThread() {
		ArrayList<VelocityZero> arr = new ArrayList<VelocityZero>();

		if (destination[0] == 0.0f) {
			x_flag = true;
		}
		if (destination[1] == 0.0f) {
			y_flag = true;
		}
		if (destination[2] == 0.0f) {
			z_flag = true;
		}

		// 最优SHC算法(即循环n2次SHC算法,取fitness最大)
		for (int i = 0; i < n2; i++) {
			VelocityZero v = new VelocityZero();
			v.CalDistance(destination, t);
			v.CalFitness();

			VelocityZero v2 = new VelocityZero();
			v2.CalDistance(destination, t);
			v2.CalFitness();

			if (v.getFitness() > v2.getFitness()) {
				vel.add(v);
				v.GenDistance(t);
				VelocityZero tmp = recursion(v, n1);
				arr.add(tmp);
				// System.out.println("Result:");
				// System.out.println("Fitness: " + tmp.getFitness());
				// System.out.println("Velocity: vx: " + tmp.getVx() + " vy:
				// " +
				// tmp.getVy() + " vz: " + tmp.getVz());
				// System.out.println("Distance: dx: " + tmp.getDx() + " dy:
				// " +
				// tmp.getDy() + " dz: " + tmp.getDz());
			} else {
				vel.add(v2);
				v2.GenDistance(t);
				VelocityZero tmp = recursion(v2, n1);
				arr.add(tmp);
				// System.out.println("Result:");
				// System.out.println("Fitness: " + tmp.getFitness());
				// System.out.println("Velocity: vx: " + tmp.getVx() + " vy:
				// " +
				// tmp.getVy() + " vz: " + tmp.getVz());
				// System.out.println("Distance: dx: " + tmp.getDx() + " dy:
				// " +
				// tmp.getDy() + " dz: " + tmp.getDz());
			}
		}

		for (int x = 0; x < arr.size(); x++) {
			System.out.println(arr.get(x).getDx() + "; " + arr.get(x).getDy() + "; " + arr.get(x).getDz() + "; ");
		}

		System.exit(0);

		// for(int i = 0; i<vel.size(); i++){
		// System.out.println((i + 1) +".Dx: " + vel.get(i).getDx() + ";Dy: " +
		// vel.get(i).getDy() + ";Dz: " + vel.get(i).getDz() + "\r\n");
		// }

		// MGA算法(即将n2个SHC算法的解,随机抽选,判断f值,并交换一个方向的v)
		for (int i = 0; i < n2; i++) {
			int val1 = (int) (Math.random() * n2);
			int val2 = (int) (Math.random() * n2);

			if (arr.get(val1).getFitness() > arr.get(val2).getFitness()) {
				// 如果随机选择到为0的轴,则重新生成随机数
				int which = -1;
				while (true) {
					which = (int) (Math.random() * 3);
					if (x_flag && (which == 0))
						continue;
					if (y_flag && (which == 1))
						continue;
					if (z_flag && (which == 2))
						continue;
					else
						break;
				}

				switch (which) {
				case 0: {
					arr.get(val2).ChangeDistance(which, 0 - arr.get(val2).getVx(), t);
					arr.get(val2).setVx(arr.get(val1).getVx());
					arr.get(val2).ChangeDistance(which, arr.get(val2).getVx(), t);
					arr.get(val2).CalDistance2(destination, t);
					arr.get(val2).CalFitness();
					break;
				}
				case 1: {
					arr.get(val2).ChangeDistance(which, 0 - arr.get(val2).getVy(), t);
					arr.get(val2).setVy(arr.get(val1).getVy());
					arr.get(val2).ChangeDistance(which, arr.get(val2).getVy(), t);
					arr.get(val2).CalDistance2(destination, t);
					arr.get(val2).CalFitness();
					break;
				}
				case 2: {
					arr.get(val2).ChangeDistance(which, 0 - arr.get(val2).getVz(), t);
					arr.get(val2).setVz(arr.get(val1).getVz());
					arr.get(val2).ChangeDistance(which, arr.get(val2).getVz(), t);
					arr.get(val2).CalDistance2(destination, t);
					arr.get(val2).CalFitness();
					break;
				}
				default: {
					break;
				}
				}
			} else if (arr.get(val1).getFitness() < arr.get(val2).getFitness()) {
				int which = (int) (Math.random() * 3);
				switch (which) {
				case 0: {
					arr.get(val1).ChangeDistance(which, 0 - arr.get(val1).getVx(), t);
					arr.get(val1).setVx(arr.get(val2).getVx());
					arr.get(val1).ChangeDistance(which, arr.get(val1).getVx(), t);
					arr.get(val1).CalDistance2(destination, t);
					arr.get(val1).CalFitness();
					break;
				}
				case 1: {
					arr.get(val1).ChangeDistance(which, 0 - arr.get(val1).getVy(), t);
					arr.get(val1).setVy(arr.get(val2).getVy());
					arr.get(val1).ChangeDistance(which, arr.get(val1).getVy(), t);
					arr.get(val1).CalDistance2(destination, t);
					arr.get(val1).CalFitness();
					break;
				}
				case 2: {
					arr.get(val1).ChangeDistance(which, 0 - arr.get(val1).getVz(), t);
					arr.get(val1).setVz(arr.get(val2).getVz());
					arr.get(val1).ChangeDistance(which, arr.get(val1).getVz(), t);
					arr.get(val1).CalDistance2(destination, t);
					arr.get(val1).CalFitness();
					break;
				}
				default: {
					break;
				}
				}
			} else {
				continue;
			}
		}

		VelocityZero result = new VelocityZero();
		result.setFitness(0.0f);

		for (int i = 0; i < arr.size(); i++) {
			if (result.getFitness() >= arr.get(i).getFitness()) {
				;
			} else {
				result = arr.get(i);
			}
		}

		System.out.println("Result:");
		System.out.println("Fitness: " + result.getFitness());
		System.out.println("Velocity: vx: " + result.getVx() + " vy: " + result.getVy() + " vz: " + result.getVz());
		System.out.println("Distance: dx: " + result.getDx() + " dy: " + result.getDy() + " dz: " + result.getDz());

		synchronized (this) {
			new FileOp().writeFile(result.getDx() + "\r\n", "Dx.txt", true);
			new FileOp().writeFile(result.getDy() + "\r\n", "Dy.txt", true);
			new FileOp().writeFile(result.getDz() + "\r\n", "Dz.txt", true);
		}
	}

	public void continueCal() {
		ArrayList<VelocityZero> arr = new ArrayList<VelocityZero>();

		if (destination[0] == 0.0f) {
			x_flag = true;
		}
		if (destination[1] == 0.0f) {
			y_flag = true;
		}
		if (destination[2] == 0.0f) {
			z_flag = true;
		}

		// 最优SHC算法(即循环n2次SHC算法,取fitness最大)
		for (int i = 0; i < n2; i++) {
			VelocityZero v = new VelocityZero();
			v.CalDistance(destination, t);
			v.CalFitness();

			VelocityZero v2 = new VelocityZero();
			v2.CalDistance(destination, t);
			v2.CalFitness();

			if (v.getFitness() > v2.getFitness()) {
				vel.add(v);
				v.GenDistance(t);
				VelocityZero tmp = recursion(v, n1);
				arr.add(tmp);
			} else {
				vel.add(v2);
				v2.GenDistance(t);
				VelocityZero tmp = recursion(v2, n1);
				arr.add(tmp);
			}
		}

		// MGA算法(即将n2个SHC算法的解,随机抽选,判断f值,并交换一个方向的v)
		for (int i = 0; i < n2; i++) {
			int val1 = (int) (Math.random() * n2);
			int val2 = (int) (Math.random() * n2);

			if (arr.get(val1).getFitness() > arr.get(val2).getFitness()) {
				// 如果随机选择到为0的轴,则重新生成随机数
				int which = -1;
				while (true) {
					which = (int) (Math.random() * 3);
					if (x_flag && (which == 0))
						continue;
					if (y_flag && (which == 1))
						continue;
					if (z_flag && (which == 2))
						continue;
					else
						break;
				}

				switch (which) {
				case 0: {
					arr.get(val2).ChangeDistance(which, 0 - arr.get(val2).getVx(), t);
					arr.get(val2).setVx(arr.get(val1).getVx());
					arr.get(val2).ChangeDistance(which, arr.get(val2).getVx(), t);
					arr.get(val2).CalDistance2(destination, t);
					arr.get(val2).CalFitness();
					break;
				}
				case 1: {
					arr.get(val2).ChangeDistance(which, 0 - arr.get(val2).getVy(), t);
					arr.get(val2).setVy(arr.get(val1).getVy());
					arr.get(val2).ChangeDistance(which, arr.get(val2).getVy(), t);
					arr.get(val2).CalDistance2(destination, t);
					arr.get(val2).CalFitness();
					break;
				}
				case 2: {
					arr.get(val2).ChangeDistance(which, 0 - arr.get(val2).getVz(), t);
					arr.get(val2).setVz(arr.get(val1).getVz());
					arr.get(val2).ChangeDistance(which, arr.get(val2).getVz(), t);
					arr.get(val2).CalDistance2(destination, t);
					arr.get(val2).CalFitness();
					break;
				}
				default: {
					break;
				}
				}
			} else if (arr.get(val1).getFitness() < arr.get(val2).getFitness()) {
				int which = (int) (Math.random() * 3);
				switch (which) {
				case 0: {
					arr.get(val1).ChangeDistance(which, 0 - arr.get(val1).getVx(), t);
					arr.get(val1).setVx(arr.get(val2).getVx());
					arr.get(val1).ChangeDistance(which, arr.get(val1).getVx(), t);
					arr.get(val1).CalDistance2(destination, t);
					arr.get(val1).CalFitness();
					break;
				}
				case 1: {
					arr.get(val1).ChangeDistance(which, 0 - arr.get(val1).getVy(), t);
					arr.get(val1).setVy(arr.get(val2).getVy());
					arr.get(val1).ChangeDistance(which, arr.get(val1).getVy(), t);
					arr.get(val1).CalDistance2(destination, t);
					arr.get(val1).CalFitness();
					break;
				}
				case 2: {
					arr.get(val1).ChangeDistance(which, 0 - arr.get(val1).getVz(), t);
					arr.get(val1).setVz(arr.get(val2).getVz());
					arr.get(val1).ChangeDistance(which, arr.get(val1).getVz(), t);
					arr.get(val1).CalDistance2(destination, t);
					arr.get(val1).CalFitness();
					break;
				}
				default: {
					break;
				}
				}
			} else {
				continue;
			}
		}

		VelocityZero result = new VelocityZero();
		result.setFitness(0.0f);

		for (int i = 0; i < arr.size(); i++) {
			if (result.getFitness() >= arr.get(i).getFitness()) {
				;
			} else {
				result = arr.get(i);
			}
		}

//		System.out.println("Result:");
//		System.out.println("Fitness: " + result.getFitness());
//		System.out.println("Velocity: vx: " + result.getVx() + " vy: " + result.getVy() + " vz: " + result.getVz());
//		System.out.println("Distance: dx: " + result.getDx() + " dy: " + result.getDy() + " dz: " + result.getDz());

		int Dx_count = (int) Math.round((result.getDx() / 4.5 * 4500));
		int Dy_count = (int) Math.round((result.getDy() / 4.5 * 4500));
		int Dz_count = (int) Math.round((result.getDz() / 4.5 * 4500));

		new FileOp().writeFile((Dx_count) + ";", "continueData.txt", true);
		new FileOp().writeFile((Dy_count) + ";", "continueData.txt", true);
		new FileOp().writeFile((Dz_count) + "\r\n", "continueData.txt", true);
		
		new FileOp().writeFile((Dx_count - Dx_count_org) + ";", "machineData.txt", true);
		new FileOp().writeFile((Dy_count - Dy_count_org) + ";", "machineData.txt", true);
		new FileOp().writeFile((Dz_count - Dz_count_org) + "\r\n", "machineData.txt", true);
		
		Dx_count_org = Dx_count;
		Dy_count_org = Dy_count;
		Dz_count_org = Dz_count;
	}

	public VelocityZero recursion(VelocityZero v1, int n) {
		VelocityZero v2 = new VelocityZero();
		v2.UpdateDistance(v1);
		v2.CalDistance(destination, t);
		v2.CalFitness();

		if (v1.getFitness() > v2.getFitness()) {

			if (n > 0) {
				vel.add(v1);
				return recursion(v1, n - 1);
			} else {
				return v1;
			}
		} else {
			if (n > 0) {
				vel.add(v2);
				v2.GenDistance(t);
				return recursion(v2, n - 1);
			} else {
				return v2;
			}
		}
	}
	
	public void setDestination(float[] destination) {
		this.destination = destination;
	}
}

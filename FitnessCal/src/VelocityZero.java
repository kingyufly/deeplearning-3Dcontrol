public class VelocityZero {
	private float vx;
	private float vy;
	private float vz;
	private float dx;
	private float dy;
	private float dz;
	private float fitness;
	private float distance;

	public VelocityZero() {
		if(Fitness_Cal.x_flag)
			this.vx = 0;
		else
			this.vx = this.GenRandomVelocity();
		
		if(Fitness_Cal.y_flag)
			this.vy = 0;
		else
			this.vy = this.GenRandomVelocity();
		
		if(Fitness_Cal.z_flag)
			this.vz = 0;
		else
			this.vz = this.GenRandomVelocity();
	}

	public float GenRandomVelocity() {
		float velocity = (float) (Math.random() * 10 - 3);
		return velocity;
	}

	public void GenDistance(float t) {
		this.dx = this.dx + this.vx * t;
		this.dy = this.dy + this.vy * t;
		this.dz = this.dz + this.vz * t;
	}

	public void ChangeDistance(int which, float value, float t) {
		switch (which) {
		case 0: {
			this.dx = this.dx + value * t;
			break;
		}
		case 1: {
			this.dy = this.dy + value * t;
			break;
		}
		case 2: {
			this.dz = this.dz + value * t;
			break;
		}
		default: {
			break;
		}
		}
	}

	public void UpdateDistance(VelocityZero v) {
		this.dx = v.getDx();
		this.dy = v.getDy();
		this.dz = v.getDz();
	}

	public void CalDistance(float[] destination, float t) {
		this.distance = (float) (Math
				.sqrt(Math.pow((this.getVx() * t + this.dx - destination[0]), 2)
						+ Math.pow((this.getVy() * t + this.dy - destination[1]), 2))
				+ Math.pow((this.getVz() * t + this.dz - destination[2]), 2));
	}

	public void CalDistance2(float[] destination, float t) {
		this.distance = (float) Math.sqrt(Math.pow((this.dx - destination[0]), 2) + Math.pow((this.dy - destination[1]), 2)
				+ Math.pow((this.dz - destination[2]), 2));
	}

	public void CalFitness() {
		this.fitness = (float) (1 / Math.pow(Math.E, this.distance));
	}

	public float getVx() {
		return vx;
	}

	public float getVy() {
		return vy;
	}

	public float getVz() {
		return vz;
	}

	public void setVx(float vx) {
		this.vx = vx;
	}

	public void setVy(float vy) {
		this.vy = vy;
	}

	public void setVz(float vz) {
		this.vz = vz;
	}

	public float getFitness() {
		return fitness;
	}

	public float getDistance() {
		return distance;
	}

	public float getDx() {
		return dx;
	}

	public float getDy() {
		return dy;
	}

	public float getDz() {
		return dz;
	}

	public void setFitness(float fitness) {
		this.fitness = fitness;
	}
	
	public String toString(){
		return this.getDx() + " " + this.getDy() + " " + this.getDz() + "\r\n";
	}
}

// 包含SHC算法,最优SHC算法,MGA算法,目标点判0

public class Test {
	public static void main(String args[]) {
		// 生成MGA密度图:先多次进行MGA运算,将结果储存在 工程根目录下的 Dx.txt Dy.txt
		// Dz.txt中,再通过Matlab进行读取并绘图(对应dotDencity.m)
		// for (int i = 0; i < 1; i++) {
		// // new Thread(new Fitness_Cal()).start();
		// new Fitness_Cal().notThread();
		// }

		// 生成SHC不判零的轨迹图:先生成不判零的SHC,将其轨迹点存储在
		// 工程根目录下的dataNotZero.txt中,再通过Matlab进行读取并绘图 (对应trackGraph.m)
		// SingleSHC shc = new SingleSHC();
		// float[] destination = { 2.0f, 1.5f, 1.0f };
		// shc.setDestination(destination);
		// shc.runNotZero();

		// 生成SHC判零的轨迹图:先生成判零的SHC,将其轨迹点存储在 工程根目录下的dataZero.txt中,再通过Matlab进行读取并绘图
		// (对应trackGraph.m)
		// SingleSHC shc = new SingleSHC();
		// float[] destination = { 2.0f, 1.5f, 1.0f };
		// shc.setDestination(destination);
		// shc.runZero();

		// 计算连续的点,最终结果储存在 工程目录的machineData.txt中
		float[][] destinations = { { 2.0f, 1.5f, 1.0f }, { -2.0f, -1.5f, -1.0f }, { 2.0f, 1.5f, 1.0f },
				{ -2.0f, -1.5f, -1.0f }, { 2.0f, 1.5f, 1.0f } };
		Fitness_Cal f = new Fitness_Cal();
		for (int i = 0; i < destinations.length; i++) {
			f.setDestination(destinations[i]);
			f.continueCal();
		}
	}
}

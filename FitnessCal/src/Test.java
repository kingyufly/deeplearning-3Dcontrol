// ����SHC�㷨,����SHC�㷨,MGA�㷨,Ŀ�����0

public class Test {
	public static void main(String args[]) {
		// ����MGA�ܶ�ͼ:�ȶ�ν���MGA����,����������� ���̸�Ŀ¼�µ� Dx.txt Dy.txt
		// Dz.txt��,��ͨ��Matlab���ж�ȡ����ͼ(��ӦdotDencity.m)
		// for (int i = 0; i < 1; i++) {
		// // new Thread(new Fitness_Cal()).start();
		// new Fitness_Cal().notThread();
		// }

		// ����SHC������Ĺ켣ͼ:�����ɲ������SHC,����켣��洢��
		// ���̸�Ŀ¼�µ�dataNotZero.txt��,��ͨ��Matlab���ж�ȡ����ͼ (��ӦtrackGraph.m)
		// SingleSHC shc = new SingleSHC();
		// float[] destination = { 2.0f, 1.5f, 1.0f };
		// shc.setDestination(destination);
		// shc.runNotZero();

		// ����SHC����Ĺ켣ͼ:�����������SHC,����켣��洢�� ���̸�Ŀ¼�µ�dataZero.txt��,��ͨ��Matlab���ж�ȡ����ͼ
		// (��ӦtrackGraph.m)
		// SingleSHC shc = new SingleSHC();
		// float[] destination = { 2.0f, 1.5f, 1.0f };
		// shc.setDestination(destination);
		// shc.runZero();

		// ���������ĵ�,���ս�������� ����Ŀ¼��machineData.txt��
		float[][] destinations = { { 2.0f, 1.5f, 1.0f }, { -2.0f, -1.5f, -1.0f }, { 2.0f, 1.5f, 1.0f },
				{ -2.0f, -1.5f, -1.0f }, { 2.0f, 1.5f, 1.0f } };
		Fitness_Cal f = new Fitness_Cal();
		for (int i = 0; i < destinations.length; i++) {
			f.setDestination(destinations[i]);
			f.continueCal();
		}
	}
}

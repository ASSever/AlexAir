class B
{
	private int x;
	protected int y;
	public int z;
	B(int x=0,int y=0,int z=0):x(x),y(y),z(z){}
	void fb(){x++;y++;y++;}
};
class D:public/*protected*/ B
{
public:
}
void main()
{
	D d;

	d.x++;
	d.y++;
	d.z++;
	B* b=&d;
}
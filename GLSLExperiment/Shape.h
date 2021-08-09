#include "Angel.h"

typedef vec4 point4;
typedef vec4 color4;

namespace Angel
{
/* --------------------------------------------------------------------------------------- */
	class Cube
	{

	public:

		const static int NumPoints = 36; /*Cạnh bên + 2 mặt*/
		int start = 0;

		static Cube quickSetup(point4 new_points[], color4 new_colors[], vec3 new_normals[], int start);

		void initCube();
		void makeColorCube();
		void ref(point4 new_points[], color4 new_colors[], vec3 new_normals[], int start);

	private:

		point4 points[NumPoints]; /* Danh sách các đỉnh cần vẽ  */
		color4 colors[NumPoints]; /* Danh sách các màu tương ứng cho các đỉnh trên*/
		vec3 normals[NumPoints]; /*Danh sách các vector pháp tuyến ứng với mỗi đỉnh*/  // PHẦN CHiẾU SÁNG

		point4 vertices[8]; /* Danh sách các đỉnh hình lập phương */
		color4 vertex_colors[8]; /*Danh sách các màu của đỉnh hình lập phương*/

		int Index = 0;
		GLfloat width = 1.0;
		color4 colorArray[8] = {
				color4(1, 0, 1, 1.0),
				color4(1, 0, 1, 1.0),
				color4(1, 0, 1, 1.0),
				color4(1, 0, 1, 1.0),
				color4(1, 0, 1, 1.0),
				color4(1, 0, 1, 1.0),
				color4(1, 0, 1, 1.0),
				color4(1, 0, 1, 1.0)
		};

		void quad(int a, int b, int c, int d);
	};

	Cube Cube::quickSetup(point4 new_points[], color4 new_colors[], vec3 new_normals[], int start)
	{
		Cube c;

		c.initCube();
		c.makeColorCube();
		c.ref( new_points, new_colors, new_normals, start );

		c.start = start;
		return c;
	}

	void Cube::initCube()
	{
		width /= 2;
		// Gán giá trị tọa độ vị trí cho các đỉnh của hình lập phương
		vertices[0] = point4(-width, -width, width, 1.0);
		vertices[1] = point4(-width, width, width, 1.0);
		vertices[2] = point4(width, width, width, 1.0);
		vertices[3] = point4(width, -width, width, 1.0);
		vertices[4] = point4(-width, -width, -width, 1.0);
		vertices[5] = point4(-width, width, -width, 1.0);
		vertices[6] = point4(width, width, -width, 1.0);
		vertices[7] = point4(width, -width, -width, 1.0);

		// Gán giá trị màu sắc cho các đỉnh của hình lập phương	
		for (int i = 0; i < 8; i++)
			vertex_colors[i] = colorArray[i];
	}

	void Cube::quad(int a, int b, int c, int d)  /*Tạo một mặt hình lập phương = 2 tam giác, gán màu cho mỗi đỉnh tương ứng trong mảng colors*/
	{
		// PHẦN CHIẾU SÁNG
		vec4 u = vertices[b] - vertices[a];
		vec4 v = vertices[c] - vertices[b];
		vec3 normal = normalize(cross(u, v)); /*vector pháp tuyến của mặt phằng*/

		normals[Index] = normal;  colors[Index] = vertex_colors[a]; points[Index++] = vertices[a];
		normals[Index] = normal;  colors[Index] = vertex_colors[b]; points[Index++] = vertices[b];
		normals[Index] = normal;  colors[Index] = vertex_colors[c]; points[Index++] = vertices[c];
		normals[Index] = normal;  colors[Index] = vertex_colors[a]; points[Index++] = vertices[a];
		normals[Index] = normal;  colors[Index] = vertex_colors[c]; points[Index++] = vertices[c];
		normals[Index] = normal;  colors[Index] = vertex_colors[d]; points[Index++] = vertices[d];
	}

	void Cube::makeColorCube(void)  /* Sinh ra 12 tam giác: 36 đỉnh, 36 màu*/
	{
		quad(1, 0, 3, 2);
		quad(2, 3, 7, 6);
		quad(3, 0, 4, 7);
		quad(6, 5, 1, 2);
		quad(4, 5, 6, 7);
		quad(5, 4, 0, 1);
	}

	void Cube::ref(point4 new_points[], color4 new_colors[], vec3 new_normals[], int start)
	{
		for (int i = start; i < start + NumPoints; i++)
		{
			new_points[i] = points[i - start];
			new_colors[i] = colors[i - start];
			new_normals[i] = normals[i - start];
		}
	}

/* --------------------------------------------------------------------------------------- */
	class Cylinder
	{
	public:

		const static int p = 60; // Số các điểm trên đường tròn
		float r = 0.5f, h = 1.0f;  // chỉ số hình trụ
		const static int NumPoints = p * 6 + 2 * p * 3; /*Cạnh bên + 2 mặt*/
		int start = 0;

		static Cylinder quickSetup(point4 new_points[], color4 new_colors[], vec3 new_normals[], int start);
		
		void initCylinder();
		void makeColorCylinder();
		void ref(point4 new_points[], color4 new_colors[], vec3 new_normals[], int start);

	private:

		point4 points[NumPoints]; /* Danh sách các đỉnh cần vẽ  */
		color4 colors[NumPoints]; /* Danh sách các màu tương ứng cho các đỉnh trên*/
		vec3 normals[NumPoints]; /*Danh sách các vector pháp tuyến ứng với mỗi đỉnh*/  // PHẦN CHiẾU SÁNG

		point4 vertices_up[p], vertices_down[p]; /* Danh sách các đỉnh đường tròn trên, dưới*/
		color4 vertex_colors_up[p], vertex_colors_down[p]; /*Danh sách các màu của đỉnh*/

		int Index = 0;
		
		
		void quad(int a, int b, int c, int d);
		void circle(int a, int b);
		
	};

	Cylinder Cylinder::quickSetup(point4 new_points[], color4 new_colors[], vec3 new_normals[], int start)
	{
		Cylinder c;

		c.initCylinder();
		c.makeColorCylinder();
		c.ref(new_points, new_colors, new_normals, start);

		c.start = start;
		return c;
	}

	void Cylinder::initCylinder()
	{
		// khởi tạo các biến số học
		int deg = 360;

		float alpha = (float)deg / p;

		// điểm khởi đầu
		float start = 0;

		for (int i = 0; i < p; i++)
		{
			// dịch chuyển 1 góc alpha
			start += alpha;

			// tính tọa độ
			float x, y;
			x = r * cos( start * DegreesToRadians ); printf("x = %f", x);
			y = r * sin( start * DegreesToRadians ); printf(", y = %f, z = %f  \n", y, h / 2);

			// lưu trữ các điểm và tạo mã màu 
			// mặt trên 
			vertices_up[i] = point4(x, y, h / 2, 1.0);
			vertex_colors_up[i] = color4(x, y, 0.0, 1.0);
			// mặt dưới
			vertices_down[i] = point4(x, y, -h / 2, 1.0);
			vertex_colors_down[i] = color4(x, y, 0.0, 1.0);
		}
	}

	void Cylinder::quad(int a, int b, int c, int d)  /*Tạo một mặt hình lập phương = 2 tam giác, gán màu cho mỗi đỉnh tương ứng trong mảng colors*/
	{
		// PHẦN CHIẾU SÁNG
		vec4 u = vertices_down[b] - vertices_up[a];
		vec4 v = vertices_down[c] - vertices_down[b];
		vec3 normal = normalize(cross(u, v)); /*vector pháp tuyến của mặt phằng*/

		normals[Index] = normal;	colors[Index] = vertex_colors_up[a];	points[Index++] = vertices_up[a];
		normals[Index] = normal;	colors[Index] = vertex_colors_down[a];	points[Index++] = vertices_down[b];
		normals[Index] = normal;	colors[Index] = vertex_colors_down[a];	points[Index++] = vertices_down[c];
		normals[Index] = normal;	colors[Index] = vertex_colors_up[a];	points[Index++] = vertices_up[a];
		normals[Index] = normal;	colors[Index] = vertex_colors_down[a];	points[Index++] = vertices_down[c];
		normals[Index] = normal;	colors[Index] = vertex_colors_up[a];	points[Index++] = vertices_up[d];
	}

	void Cylinder::circle(int a, int b) /*Tạo một mặt hình tròn bằng cách nối các điểm đồng tâm*/
	{
		point4 center_up = point4(0.0f, 0.0f, h / 2, 1.0f);
		point4 center_down = point4(0.0f, 0.0f, -h / 2, 1.0f);
		color4 color_up = color4(0.0f, 0.6f, 0.5f, 1.0f);
		color4 color_down = color4(0.0f, 0.6f, 0.5f, 1.0f);

		// PHẦN CHIẾU SÁNG
		vec4 u_up = vertices_up[a] - center_up;
		vec4 v_up = vertices_up[b] - vertices_up[a];
		vec3 normal_up = normalize(cross(u_up, v_up)); /*vector pháp tuyến của mặt phằng*/

		// thêm điểm làm tâm hình tròn nắp trên
		normals[Index] = normal_up;		colors[Index] = color_up;				points[Index++] = center_up;
		// 2 điểm gần kề
		normals[Index] = normal_up;		colors[Index] = vertex_colors_up[a];	points[Index++] = vertices_up[a];
		normals[Index] = normal_up;		colors[Index] = vertex_colors_up[a];	points[Index++] = vertices_up[b];

		// PHẦN CHIẾU SÁNG
		vec4 u_down = vertices_down[a] - center_down;
		vec4 v_down = vertices_down[b] - vertices_down[a];
		vec3 normal_down = normalize(cross(u_down, v_down)); /*vector pháp tuyến của mặt phằng*/

		// thêm điểm làm tâm hình tròn nắp dưới
		normals[Index] = -normal_down;		colors[Index] = color_down;				points[Index++] = center_down;
		// 2 điểm gần kề
		normals[Index] = -normal_down;		colors[Index] = vertex_colors_down[a];	points[Index++] = vertices_down[a];
		normals[Index] = -normal_down;		colors[Index] = vertex_colors_down[a];	points[Index++] = vertices_down[b];
	}

	void Cylinder::makeColorCylinder(void)  /* Sinh ra 12 tam giác: 36 đỉnh, 36 màu*/
	{
		int up, down;
		for (int i = 0; i < p; i++)
		{
			up = i;
			down = i == p - 1 ? 0 : i + 1; // đóng vòng tròn

			quad(up, up, down, down);
			circle(up, down);
		}
	}

	void Cylinder::ref(point4 new_points[], color4 new_colors[], vec3 new_normals[], int start)
	{
		for (int i = start; i < start + NumPoints; i++)
		{
			new_points[i] = points[i - start];
			new_colors[i] = colors[i - start];
			new_normals[i] = normals[i - start];
		}
	}

/* --------------------------------------------------------------------------------------- */
	class CustomShape
	{
	public:

		const static int MaxPoints = 3000; /*Số đỉnh max*/
		int NumPoints = 0; /*Số đỉnh thực tế*/
		int start = 0; /*Vị trí bắt đầu trong mảng*/
		
		vec3 normals[MaxPoints]; /*Danh sách các vector pháp tuyến ứng với mỗi đỉnh*/  // PHẦN CHiẾU SÁNG
		static CustomShape quickSetup(point4 new_points[MaxPoints], vec3 new_normals[], int num_points, int &start); /* Khởi tạo nhanh 1 shape*/
		CustomShape changeMaterial(vec4 material_diffuse, vec4 material_ambient, vec4 material_specular, GLfloat material_shininess);

		void init(point4 new_points[MaxPoints], int start); /*Lưu tọa độ các điểm phục vụ tính toán*/
		void makeCustomShape(); /*Tạo logic hình thành vật thể*/
		void ref(vec3 new_normals[], int start); /*Tham chiếu đến đối tượng thực*/
		void updateMaterial(vec4 &material_diffuse, vec4 &material_ambient, vec4 &material_specular, GLfloat &material_shininess);
		void log(point4 points[MaxPoints], int start); /*In kết quả lên console để kiểm soát lỗi*/

	private:

		point4 vertices[MaxPoints]; /* Danh sách các đỉnh hình lập phương */

		// Chất liệu mặc định
		vec4 material_diffuse = vec4(1.0f, 0.8f, 0.0f, 1.0f);
		vec4 material_ambient = vec4(1.0f, 0.0f, 1.0f, 1.0f);
		vec4 material_specular = vec4(1.0f, 0.8f, 0.0f, 1.0f);
		GLfloat material_shininess = 100.0f;

		int Index = 0;
		void triangle(int a, int b, int c); /*Tạo các tam giác từ các điểm theo thứ tự*/
	};

	CustomShape CustomShape::quickSetup(point4 new_points[MaxPoints], vec3 new_normals[], int num_points, int &start)
	{
		CustomShape shape;
		shape.NumPoints = num_points;

		shape.init(new_points, start);
		shape.makeCustomShape();
		shape.ref(new_normals, start);
		//shape.log(new_points, start)

		start += num_points; /*Update số start cho lần tiếp theo*/
		return shape;
	}

	CustomShape CustomShape::changeMaterial(vec4 material_diffuse, vec4 material_ambient, vec4 material_specular, GLfloat material_shininess)
	{
		this->material_diffuse = material_diffuse == NULL ? this->material_diffuse : material_diffuse;
		this->material_ambient = material_ambient == NULL ? this->material_ambient : material_ambient;
		this->material_specular = material_specular == NULL ? this->material_specular : material_specular;
		this->material_shininess = material_shininess == NULL ? this->material_shininess : material_shininess;

		return *this;
	}

	void CustomShape::updateMaterial(vec4 &material_diffuse, vec4 &material_ambient, vec4 &material_specular, GLfloat &material_shininess) 
	{
		material_diffuse = this->material_diffuse;
		material_ambient = this->material_ambient;
		material_specular = this->material_specular;
		material_shininess = this->material_shininess;

		/*printf("diffuse: ( %f, %f, %f, %f ) , ambient: ( %f, %f, %f, %f ), material_specular: ( %f, %f, %f, %f ); shininess: %f\n",
			material_diffuse.x, material_diffuse.y, material_diffuse.z, material_diffuse.w,
			material_ambient.x, material_ambient.y, material_ambient.z, material_ambient.w,
			material_specular.x, material_specular.y, material_specular.z, material_specular.w,
			material_shininess);*/
	}

	void CustomShape::init(point4 new_points[MaxPoints], int start)
	{
		for (int i = start; i < start + NumPoints; i++)
		{
			vertices[i - start] = new_points[i];
		}

		this->start = start;
	}

	void CustomShape::triangle(int a, int b, int c)
	{
		// PHẦN CHIẾU SÁNG
		vec4 u = vertices[b] - vertices[a];
		vec4 v = vertices[c] - vertices[b];
		vec3 normal = normalize(cross(u, v)); /*vector pháp tuyến của mặt phằng*/

		// lưu pháp tuyến của 3 đỉnh liền kề
		normals[Index++] = normal;
		normals[Index++] = normal;
		normals[Index++] = normal;
	}

	void CustomShape::makeCustomShape(void)
	{
		for (int i = 0; i < NumPoints - 2; i = i + 3) // i+=3 để không điểm nào bị ghi đè pháp tuyến
		{
			// chỉ thực hiện tính pháp tuyến của 3 đỉnh gần nhau (vì đã có sẵn points và colors rồi) 
			triangle(i, i + 1, i + 2);
		}
	}

	void CustomShape::ref(vec3 new_normals[], int start)
	{
		for (int i = start; i < start + NumPoints; i++)
		{
			new_normals[i] = normals[i - start];
		}
	}

	void CustomShape::log(point4 points[MaxPoints], int start)
	{
		printf("!!! Custom shape: \n");
		for (int i = start; i < start + NumPoints; i++)
		{
			printf("p%d (%f, %f, %f, %f) \n", i, points[i].x, points[i].y, points[i].z, points[i].w);
		}
	}
}
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>

GLfloat theta = -60;
GLfloat up = 1; //팔을 올림, up==0이면 팔을 내림
GLfloat shakeWhole = 1; //팔을 전체 올림, shakeWhole==0이면 팔을 아래부분만 올림

static int shoulder = 0, elbow = 0, wrist = 0;

/*머리 그리기*/
void Draw_Head() { 
	double rad = 0.38;
	glBegin(GL_POLYGON);
	glColor3f(0.956863f, 0.643137f, 0.376471f);
	for (int i = 0; i < 360; i++) {
		double angle = i * 3.141592 / 180;
		glVertex2f(rad * cos(angle), 0.9 + rad * sin(angle)); //머리는 2D원이기 때문에 360도로 계속 각을 늘려가면서 표현
	}
	glEnd();
	glFlush();
}

/*몸 그리기*/
void Draw_Body() { 
	glBegin(GL_POLYGON);
	glColor3f(0.4f, 0.7f, 1.0f);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glEnd();
}

/*어깨 그리기*/
void Draw_Right_UpperArm() { //오른쪽 어깨
	glBegin(GL_POLYGON);
	glColor3f(0.4f, 0.7f, 1.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(0.7, 0.3, 0.0);
	glVertex3f(0.7, 0.0, 0.0);
	glEnd();
}

void GoToShoulderCoordinates_R() {
	glTranslatef(0.5, 0.5, 0.0);
	glRotatef(theta, 0.0, 0.0, 1.0);
	glScalef(1.0, 1.0, 1.0);
}

void Draw_Left_UpperArm() { //왼쪽 어깨
	glBegin(GL_POLYGON);
	glColor3f(0.4f, 0.7f, 1.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.7, 0.3, 0.0);
	glVertex3f(-0.7, 0.0, 0.0);
	glEnd();
}

void GoToShoulderCoordinates_L() {
	glTranslatef(-0.5, 0.5, 0.0);
	glRotatef(theta * -1, 0.0, 0.0, 1.0);
	glScalef(1.0, 1.0, 1.0);
}

/*팔뚝 그리기*/
void Draw_Right_LowerArm() { //오른쪽 팔뚝
	glBegin(GL_POLYGON);
	glColor3f(0.3f, 0.9f, 1.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(0.7, 0.3, 0.0);
	glVertex3f(0.7, 0.0, 0.0);
	glEnd();
}

void GoToElbowCoordinates_R()
{
	glTranslatef(0.7, 0.0, 0.0);
	glRotatef(theta, 0.0, 0.0, 1.0);
}

void Draw_Left_LowerArm() { //왼쪽 팔뚝
	glBegin(GL_POLYGON);
	glColor3f(0.3f, 0.9f, 1.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.7, 0.3, 0.0);
	glVertex3f(-0.7, 0.0, 0.0);
	glEnd();
}

void GoToElbowCoordinates_L()
{
	glTranslatef(-0.7, 0.0, 0.0);
	glRotatef(theta * -1, 0.0, 0.0, 1.0);
}

/*손 그리기*/
void Draw_Right_Hand() { //오른쪽 손
	glBegin(GL_POLYGON);
	glColor3f(0.4f, 0.7f, 1.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(0.25, 0.35, 0.0);
	glVertex3f(0.5, 0.15, 0.0);
	glVertex3f(0.25, -0.05, 0.0);
	glEnd();

}

void GoToWristCoordinates_R() {
	glTranslatef(0.7, 0.0, 0.0);
	glRotatef(theta, 0.0, 0.0, 1.0);
}

void Draw_Left_Hand() { //왼쪽 손
	glBegin(GL_POLYGON);
	glColor3f(0.4f, 0.7f, 1.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.25, 0.35, 0.0);
	glVertex3f(-0.5, 0.15, 0.0);
	glVertex3f(-0.25, -0.05, 0.0);
	glEnd();
}

void GoToWristCoordinates_L() {
	glTranslatef(-0.7, 0.0, 0.0);
	glRotatef(theta * -1, 0.0, 0.0, 1.0);
}


void draw_Right_Arm() { //오른쪽 팔 전체 흔들기
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); //전역 좌표계 = 모델 좌표계

	Draw_Head(); //머리 그리기
	glPushMatrix(); //전역 좌표계 저장

	Draw_Body(); //몸체 그리기
	glPushMatrix(); //전역 좌표계 저장

	GoToShoulderCoordinates_R(); //어깨 기준 모델 좌표계
	Draw_Right_UpperArm(); //위 팔 그리기
	glPushMatrix(); //어깨 기준 모델 좌표계 저장

	GoToElbowCoordinates_R(); //꿈치 기준 모델 좌표계
	Draw_Right_LowerArm(); //아래팔 그리기
	glPushMatrix(); //팔꿈치 기준 모델 좌표계 저장

	GoToWristCoordinates_R(); //손목 기준 모델 좌표계
	Draw_Right_Hand(); //손 그리기

	glPopMatrix(); //팔꿈치 좌표계 복원
	glPopMatrix(); //어깨 좌표계 복원
	glPopMatrix(); //몸체 좌표계 복원
	glPopMatrix(); //머리 좌표계 복원
}

void draw_Left_Arm() { //왼쪽 팔 전체 흔들기
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); //전역 좌표계 = 모델 좌표계

	Draw_Head(); //머리 그리기
	glPushMatrix(); //전역 좌표계 저장

	Draw_Body(); //몸체 그리기
	glPushMatrix(); //전역 좌표계 저장

	GoToShoulderCoordinates_L(); //어깨 기준 모델 좌표계
	Draw_Left_UpperArm(); //위 팔 그리기
	glPushMatrix(); //어깨 기준 모델 좌표계 저장

	GoToElbowCoordinates_L(); //꿈치 기준 모델 좌표계
	Draw_Left_LowerArm(); //아래팔 그리기
	glPushMatrix(); //팔꿈치 기준 모델 좌표계 저장

	GoToWristCoordinates_L(); //손목 기준 모델 좌표계
	Draw_Left_Hand(); //손 그리기

	glPopMatrix(); //팔꿈치 좌표계 복원
	glPopMatrix(); //어깨 좌표계 복원
	glPopMatrix(); //몸체 좌표계 복원
	glPopMatrix(); //머리 좌표계 복원
}

void draw_Lower_Right_Arm() { //오른쪽 팔 아래 흔들기
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); //전역 좌표계 = 모델 좌표계

	Draw_Head(); //머리 그리기
	glPushMatrix(); //전역 좌표계 저장

	Draw_Body(); //몸체 그리기
	glPushMatrix(); //전역 좌표계 저장

	Draw_Right_UpperArm(); //위 팔 그리기
	glPushMatrix(); //어깨 기준 모델 좌표계 저장

	GoToElbowCoordinates_R(); //꿈치 기준 모델 좌표계
	Draw_Right_LowerArm(); //아래팔 그리기
	glPushMatrix(); //팔꿈치 기준 모델 좌표계 저장

	GoToWristCoordinates_R(); //손목 기준 모델 좌표계
	Draw_Right_Hand(); //손 그리기

	glPopMatrix(); //팔꿈치 좌표계 복원
	glPopMatrix(); //어깨 좌표계 복원
	glPopMatrix(); //몸체 좌표계 복원
	glPopMatrix(); //머리 좌표계 복원
}

void draw_Lower_Left_Arm() { //왼쪽 팔 전체 흔들기
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); //전역 좌표계 = 모델 좌표계

	Draw_Head(); //머리 그리기
	glPushMatrix(); //전역 좌표계 저장

	Draw_Body(); //몸체 그리기
	glPushMatrix(); //전역 좌표계 저장


	Draw_Left_UpperArm(); //위 팔 그리기
	glPushMatrix(); //어깨 기준 모델 좌표계 저장

	GoToElbowCoordinates_L(); //꿈치 기준 모델 좌표계
	Draw_Left_LowerArm(); //아래팔 그리기
	glPushMatrix(); //팔꿈치 기준 모델 좌표계 저장

	GoToWristCoordinates_L(); //손목 기준 모델 좌표계
	Draw_Left_Hand(); //손 그리기

	glPopMatrix(); //팔꿈치 좌표계 복원
	glPopMatrix(); //어깨 좌표계 복원
	glPopMatrix(); //몸체 좌표계 복원
	glPopMatrix(); //머리 좌표계 복원
}

void MyDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if(shakeWhole == 1){ //팔 전체 흔듬
		draw_Left_Arm(); //왼쪽 전체 팔을 흔듬
		draw_Right_Arm(); //오른쪽 전체 팔을 흔듬
	}

	else if (shakeWhole == 0) { //팔 아래 부분 흔듬
		draw_Lower_Left_Arm(); //왼쪽 아래 부분 팔을 흔듬
		draw_Lower_Right_Arm(); //오른쪽 아래 부분 팔을 흔듬
	}

	glEnd();
	glutSwapBuffers();
}



void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(10, timer, 1);
}

void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
	switch (KeyPressed) {
	case 'a':
		shakeWhole = 1; //팔 전체 흔듬
		theta--;
		if (theta < -60)
			up = 1; //팔을 위로 들어올림
		break;
	case 'q':
		shakeWhole = 1; //팔 전체 흔듬
		theta++;
		if (theta > 60) 
			up = 0; //팔을 아래로 내림
		
		break;
	case 'l':
		shakeWhole =0; //팔 아래 부분 흔듬
		theta--;
		if (theta < -60)
			up = 1; //팔을 위로 들어올림

		break;
	case 'p':
		shakeWhole = 0; //팔 아래 부분 흔듬
		theta++;
		if (theta > 60)
			up = 0; //팔을 아래로 내림
		break;


	}


}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 0);
	glutCreateWindow("Arm Shaking");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3.0, 3.0, -3.0, 3.0, 1.0, -1.0);
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutTimerFunc(40, timer, 1);
	glutMainLoop();
	return 0;
}

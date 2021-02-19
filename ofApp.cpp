#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 100, true, true, true);
	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	int radius = 250;
	float phi_deg_step = 10;
	float theta_deg_step = 3;

	for (float theta_deg = theta_deg_step; theta_deg < 180; theta_deg += theta_deg_step * 2) {

		int phi_deg_start = ofGetFrameNum() * 5 + theta_deg * 2;
		for (float phi_deg = phi_deg_start; phi_deg < phi_deg_start + 250; phi_deg += phi_deg_step) {

			auto index = this->face.getNumVertices();
			vector<glm::vec3> vertices;

			vertices.push_back(glm::vec3(
				radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
			vertices.push_back(glm::vec3(
				radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
			vertices.push_back(glm::vec3(
				radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));
			vertices.push_back(glm::vec3(
				radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));

			this->face.addVertices(vertices);
			this->frame.addVertices(vertices);

			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
			this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

			this->frame.addIndex(index + 0); this->frame.addIndex(index + 1);
			this->frame.addIndex(index + 3); this->frame.addIndex(index + 2);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(239);
	ofFill();
	string word = "PCD";
	this->font.drawStringAsShapes(word, this->font.stringWidth(word) * -0.5, this->font.stringHeight(word) * 1.5);

	word = "2021";
	this->font.drawStringAsShapes(word, this->font.stringWidth(word) * -0.5, this->font.stringHeight(word) * 0);

	ofSetColor(39);
	ofNoFill();
	ofDrawRectangle(0, 0, 800, 800);

	ofRotateX(270);

	this->face.draw();

	ofSetColor(239);
	this->frame.draw();

	

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
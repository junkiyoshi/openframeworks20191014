#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);

	auto len = 30;
	ofColor in_color, out_color;
	for (auto radius = 150; radius < 300; radius += len * 2) {

		ofMesh mesh;
		for (auto deg = 0; deg < 360; deg += 1) {

			int out_radius = radius + len;
			auto in_location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			auto out_location = glm::vec2(out_radius * cos(deg * DEG_TO_RAD), out_radius * sin(deg * DEG_TO_RAD));

			mesh.addVertex(ofPoint(in_location));
			mesh.addColor(ofColor());
			mesh.addVertex(ofPoint(out_location));
			mesh.addColor(ofColor());
		}

		for (auto i = 0; i < mesh.getVertices().size(); i += 2) {

			auto index_0 = i;
			auto index_1 = (i + 1) % mesh.getVertices().size();
			auto index_2 = (i + 2) % mesh.getVertices().size();
			auto index_3 = (i + 3) % mesh.getVertices().size();

			mesh.addIndex(index_0);
			mesh.addIndex(index_1);
			mesh.addIndex(index_2);

			mesh.addIndex(index_3);
			mesh.addIndex(index_1);
			mesh.addIndex(index_2);
		}

		this->mesh_list.push_back(mesh);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofColor color;
	for (auto& mesh : this->mesh_list) {

		for (auto i = 0; i < mesh.getVertices().size(); i += 1) {

			auto location = mesh.getVertices()[i];

			color.setHsb(ofMap(ofNoise(location.x * 0.01, location.y * 0.01, ofGetFrameNum() * 0.005), 0, 1, 0, 255), 255, 255);
			mesh.setColor(i, color);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	for (auto& mesh : this->mesh_list) {
	
		mesh.draw();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
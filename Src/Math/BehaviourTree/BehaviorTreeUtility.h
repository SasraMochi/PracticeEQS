#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <json.hpp>
#include <fstream>
#include <map>
#include <nameof.hpp>

#include "imgui.h"


/// <summary>
/// �m�[�h�̎��
/// </summary>
enum class NodeType {
	Composite,
	Decorator,
	Branch,
	Leaf
};

/// <summary>
/// �m�[�h�̖��O
/// </summary>
enum class NodeName {
	Sequence,
	Selector,
	Inverter,
	CheckFarPlayer,
	CheckNearPlayer,
	ChasePlayerLeaf,
	CircleAttackLeaf,
	DebugDrawLeef,
	AlwaysFailLeaf,
	AlwaysSuccessLeaf,
	EscapeFromPlayerLeaf,
	WaitLeaf,
	NameEnd, // �v�f���擾�p
};

/// <summary>
/// �e�m�[�h�̖��O�ƃ^�C�v�̃}�b�s���O
/// </summary>
static std::map<NodeName, NodeType> NODE_MAP = {
	{NodeName::Sequence, NodeType::Composite},
	{NodeName::Selector, NodeType::Composite},
	{NodeName::Inverter, NodeType::Decorator},
	{NodeName::CheckFarPlayer, NodeType::Branch},
	{NodeName::CheckNearPlayer, NodeType::Branch},
	{NodeName::ChasePlayerLeaf, NodeType::Leaf},
	{NodeName::CircleAttackLeaf, NodeType::Leaf},
	{NodeName::DebugDrawLeef, NodeType::Leaf},
	{NodeName::AlwaysFailLeaf, NodeType::Leaf},
	{NodeName::AlwaysSuccessLeaf, NodeType::Leaf},
	{NodeName::EscapeFromPlayerLeaf, NodeType::Leaf},
	{NodeName::WaitLeaf, NodeType::Leaf},
};

/// <summary>
/// �m�[�h�̍\����
/// </summary>
struct BTNode {
	int id = 0;                             // �ŗLID
	NodeType type = NodeType::Leaf;         // �m�[�h�̃^�C�v
	NodeName name = NodeName::WaitLeaf;     // �m�[�h�̖��O
	std::vector<int> children;              // �q�m�[�hID
	int parent = -1;                        // �e�m�[�hID

	// Branch�p�̕ϐ�
	int true_child = -1;
	int false_child = -1;

	// Wait�p�̕ϐ�
	float wait_time = -1.f;

	// CheckFarPlayer, CheckNearPlayer�p�̕ϐ�
	float limit_distance = -1.f;

	// �G�f�B�^�[��ł̈ʒu
	float pos_x = 0.f;
	float pos_y = 0.f;

	// ���O��string�^�Ŏ擾
	std::string GetString() const {
		return std::string(NAMEOF_ENUM(name));
	}
};


/// <summary>
/// �m�[�h�ō\�����ꂽ�؂̍\����
/// </summary>
class BehaviorTreeGraph
{
	using json = nlohmann::json;

private:
	// �e��m�[�h�^�C�v�̃^�C�g���o�[�̐F
	const std::map<NodeType, ImU32> cNodeColors = {
		{ NodeType::Composite, IM_COL32(128, 32, 32, 255)},
		{ NodeType::Decorator, IM_COL32(32, 32, 128, 255) },
		{ NodeType::Branch,    IM_COL32(128, 128, 32, 255)},
		{ NodeType::Leaf,      IM_COL32(32, 128, 32, 255)}
	};

	const ImU32 cRunningColor = IM_COL32(250, 50, 0, 255);
	const ImU32 cLinkColor = IM_COL32(75, 75, 200, 200);

	const int cInputBit = 16;
	const int cTruePinBit = 1;
	const int cFalsePinBit = 2;

	const enum class NodeTuple {
		Node_Id,
		Child_Id,
		PinType,
	};

public:
	BehaviorTreeGraph(bool is_edit_mode);

	~BehaviorTreeGraph();

	// ������
	void initialize();

	// �X�V
	void update();

	// �`��
	void draw();

	// ���[�h�ؑ�
	void change_mode(bool is_edit_mode);

	// ���[�h����Json�t�@�C����I��
	void select_load_file();

	// ���݃��[�h���Ă���Json�t�@�C���p�X���擾
	std::string get_loading_file() const { return mLoadFileName; }

	// ���ݓ������Ă���m�[�h�ԍ���ݒ�
	void set_runnning_node_id(const int running_node_id);

private:
	// �m�[�h�̒ǉ�
	int add_node(NodeName name);

	// �����N�̒ǉ�
	void add_link(int start_attr, int end_attr);

	// Json�����o������
	void export_json(const std::string& file_name);

	// Json�ǂݍ��ݏ���
	void import_json(const std::string& file_name);

	// �m�[�h�̈ʒu���X�V
	void set_node_pos(int id, float x, float y);

	// �I�����Ă���v�f���폜
	void delete_selected_items();

private:
	// �m�[�h�̃����N���擾
	const std::unordered_map<int, std::tuple<int, int, int>>& get_node_links() const { return mNodeLinks; }

	// �m�[�h�Q���擾
	const std::unordered_map<int, BTNode>& get_nodes() const { return mNodes; }

	// �����񂩂�NodeName��Ԃ�
	NodeName get_matching_node_name(std::string name);

	// �I�����Ă���m�[�h�̐����擾
	const int get_selected_node_num() const { return static_cast<int>(mSelectedNodes.size()); }

	// �I�����Ă���m�[�h���擾
	const int get_selected_node(int index);

	// �I�����Ă��郊���N�̐����擾
	const int get_selected_link_num() const { return static_cast<int>(mSelectedLinks.size()); }

private:
	// �I�����Ă���v�f�̍X�V
	void update_selected();

	// �m�[�h�̃����N���s��
	void update_links();

	// �m�[�h�̈ړ�����
	void update_node_pos();

	// �L�[�̍X�V����
	void update_input_key();

	// �c�[���o�[�̕`��
	void draw_toolbar();

	// �G�f�B�^�[�̕`��
	void draw_editor();

private:
	// �m�[�h�ǉ��{�^���̕`��
	void draw_add_button();

	// �����o���{�^���̕`��
	void draw_export_button();

	// �ǂݍ��݃{�^���̕`��
	void draw_import_button();

	// �폜�{�^���̕`��
	void draw_delete_button();

	// �m�[�h��`��
	void draw_nodes();
	void draw_node(const BTNode& node, int node_id, bool is_selected);

	// �^�C�g����`��
	void draw_title(const BTNode& node);

	// ���̓s����`��
	void draw_input_pin(const BTNode& node);

	// �o�̓s����`��
	void draw_output_pin(const BTNode& node, bool is_selected);

	// �p�����[�^��`��
	void draw_parameter(const BTNode& node, int node_id, bool is_selected);

	// �����N��`��
	void draw_links();

private:
	// �m�[�h�̍폜
	void remove_node(int id);

	// �m�[�h�̍폜
	void remove_node(const std::vector<int>& delete_list);

	// �m�[�h�������N�ł��邩�ǂ���
	bool is_link_addable(BTNode& parent_node, BTNode& child_node, bool is_true_branch);

	// �m�[�h���m�̃����N������
	void remove_nodes_link(int parent_id, int child_id);

	// �m�[�h�̃����N���폜
	void delete_link(int id);

	// �m�[�h�̃����N���폜
	void delete_link(const std::vector<int>& delete_list);

	// ID����m�[�h������
	BTNode& get_node(int id);

	// �m�[�h��limit_distance��ݒ�
	void set_limit_distance(int id, float limit_distance);

	// �m�[�h��wait_time��ݒ�
	void set_wait_time(int id, float wait_time);

	// �m�[�h�̃����N��ǉ�(NodeLink����)
	void add_link_tuple(int parent_id, int child_id, bool is_true_branch);

	// �S�m�[�h����Enum����String�̔z��ɕϊ�
	std::vector<std::string> get_all_node_names() const;

	// �S�I��������
	void reset_selected();

	// �I�𒆂̃m�[�h�Ɋւ��郊���N��􂢏o��
	bool get_selected_nodes_related_links(std::vector<int>* links);

	// �n���ꂽ�m�[�h�Ɋւ��郊���N��􂢏o��
	bool get_nodes_related_links(const int node_id, std::vector<int>* links, bool contain_child = true);

	// �n���ꂽ�m�[�h�Ɋւ��郊���N��􂢏o��(�e�܂Ŋ܂�)
	bool get_nodes_related_all_links(const int node_id, std::vector<int>* links);

	// �n���ꂽ�m�[�h�Ɋւ���m�[�h��􂢏o��(�e�܂Ŋ܂�)
	bool get_nodes_related_all_nodes(const int node_id, std::vector<int>* nodes);

	// �֘A���郊���N���ǂ���
	bool is_related_links(const int node_id, const std::pair<int, std::tuple<int, int, int>>& node_link, bool contain_child);

	// �֘A����m�[�h���ǂ���
	bool is_related_nodes(const int node_id, const std::pair<const int, const BTNode>& node);

private:
	std::string mLoadFileName = "";

	bool mIsEditMode = true;

	std::unordered_map<int, BTNode>          mNodes;
	std::unordered_map<int, std::tuple<int, int, int>> mNodeLinks;

	int mCreatedLinkId = 0;
	int mNextId = 1;

	std::vector<int> mSelectedNodes;
	std::vector<int> mSelectedLinks;

	std::vector<std::string> mNodeNames;
	int mSelectedAddNode = 0;

	// ���A���^�C���\���p
	std::vector<int> mRunningLinks;
	std::vector<int> mRunningNodes;
};
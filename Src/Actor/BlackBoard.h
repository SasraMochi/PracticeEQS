#pragma once

#include <string>
#include <unordered_map>
#include <any>
#include <iostream>

class BlackBoard {
public:
	// �v�f���Z�b�g
	template<typename T>
	void set_value(const std::string& key, const T& value) {
		mData[key] = value;
	}

	// �v�f���擾
	template<typename T>
	T get_value(const std::string& key) const {
		auto it = mData.find(key);
		if (it != mData.end()) {
			return std::any_cast<T>(it->second);
		}

		throw std::runtime_error("�L�[��������܂���ł����F " + key);
	}

	// �L�[�����邩�`�F�b�N
	bool has_key(const std::string& key) const;

private:
	std::unordered_map<std::string, std::any> mData;
};
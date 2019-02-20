// This file is part of Tempest-core project
// Author: Karol Kontny

#include "main_thread.h"

const std::thread::id tst::core::main_thread::m_id = std::this_thread::get_id();
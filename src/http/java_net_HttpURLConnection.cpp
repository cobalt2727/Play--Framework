#include <cassert>
#include "http/java_net_HttpURLConnection.h"
#include "android/JavaVM.h"

using namespace java::net;

HttpURLConnection HttpURLConnection::CastTo(jobject src)
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = HttpURLConnection_ClassInfo::GetInstance();
	if(env->IsInstanceOf(src, classInfo.clazz) == JNI_FALSE)
	{
		throw std::runtime_error("Invalid cast");
	}
	HttpURLConnection newObject;
	newObject.Attach(src);
	return newObject;
}

void HttpURLConnection::disconnect()
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = HttpURLConnection_ClassInfo::GetInstance();
	env->CallVoidMethod(m_this, classInfo.disconnect);
	Framework::CJavaVM::CheckException(env);
}

jobject HttpURLConnection::getInputStream()
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = HttpURLConnection_ClassInfo::GetInstance();
	jobject result = env->CallObjectMethod(m_this, classInfo.getInputStream);
	Framework::CJavaVM::CheckException(env);
	assert(result != NULL);
	return result;
}

jint HttpURLConnection::getResponseCode()
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = HttpURLConnection_ClassInfo::GetInstance();
	auto result = env->CallIntMethod(m_this, classInfo.getResponseCode);
	Framework::CJavaVM::CheckException(env);
	return result;
}

void HttpURLConnection_ClassInfo::PrepareClassInfo()
{
	auto env = Framework::CJavaVM::GetEnv();
	
	jclass tmpClazz = env->FindClass("java/net/HttpURLConnection");
	Framework::CJavaVM::CheckException(env);
	assert(tmpClazz != NULL);
	clazz = reinterpret_cast<jclass>(env->NewGlobalRef(tmpClazz));
	assert(clazz != NULL);
	
	disconnect = env->GetMethodID(clazz, "disconnect", "()V");
	Framework::CJavaVM::CheckException(env);
	assert(disconnect != NULL);
	
	getInputStream = env->GetMethodID(clazz, "getInputStream", "()Ljava/io/InputStream;");
	Framework::CJavaVM::CheckException(env);
	assert(getInputStream != NULL);
	
	getResponseCode = env->GetMethodID(clazz, "getResponseCode", "()I");
	Framework::CJavaVM::CheckException(env);
	assert(getResponseCode != NULL);
}

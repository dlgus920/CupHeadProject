#include "PreCompile.h"
#include "MainLoading.h"

MainLoading::MainLoading() // default constructer 디폴트 생성자
{
	//메인 로딩씬을 재생하기 위한 최소한의 리소스를 불러온다.
	//이후 메인 로딩씬을 재생하며 타이틀맵을 재생하기 위한 리소스를 불러온다.
	// 타이틀맵에서 동작을 인식하여 다음 로딩씬을 호출하고, 그를 위한 리소스를 불러오며 다시끔 로딩씬을 재생한다.
	// 가능하면 람다 함수를 이용하여 그때그때마다 로딩씬에 필요한 함수를 정의하여 사용할 수 있도록 한다.
}

MainLoading::~MainLoading() // default destructer 디폴트 소멸자
{

}

MainLoading::MainLoading(MainLoading&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}


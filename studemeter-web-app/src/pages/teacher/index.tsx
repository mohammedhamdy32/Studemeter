import Head from "next/head";
import Container from "react-bootstrap/Container";
import Header from "@/components/Header";
import Link from "next/link";
import { useRouter } from "next/router";



function SelectMenu() {
  const options = [
    { value: 'c1_1', label: 'Classroom 1/1', isSelected: true },
    { value: 'c1_2', label: 'Classroom 1/2' },
    { value: 'c1_3', label: 'Classroom 1/3' },
    { value: 'c2_1', label: 'Classroom 2/1' },
    { value: 'c2_2', label: 'Classroom 2/2' },
  ];
  return (
    <select className="form-select form-select-lg mb-3" aria-label="Large select example">
      {options.map((option, index) => (
        <option
          key={index}
          value={option.value}
          selected={option.isSelected}
        >
          {option.label}
        </option>
      ))}
    </select>
  );
};

export default function Home() {
  const router = useRouter();
  const handleButtonClick = () => {
    router.push('/students');
  }

  const teacher_name = "Ms. Sarah";
  return (
    <>
      <Head>
        <title>Studemeter</title>
        <meta name="description" content="Students Focus Monitoring System" />
        <meta name="viewport" content="width=device-width, initial-scale=1" />
        <link rel="icon" href="/favicon.ico" />
      </Head>
      <Container as="main" className="py-4 px-3 mx-auto">
        <Header text="logout" href="/" />

        <div className="row justify-content-center">
          <form className="col-lg-6 row">
            <label className="fs-4 text-center my-5">
              Good morning,<br /><span>{teacher_name}</span>!
            </label>


            <div className="col-12 my-4 input-group-lg">
              <div className="row">
                <label className="text-muted fs-6 text-center mb-2 text-uppercase" htmlFor="classroom">
                  current classroom
                </label>
              </div>
              <SelectMenu />
            </div>


            <div className="col-12">
              <div className="row justify-content-center">
                <div className="col-auto">
                  <button type="button" onClick={handleButtonClick} className="text-capitalize btn btn-primary rounded-pill">
                    View Students
                    <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" className="bi bi-caret-right-fill" viewBox="0 0 16 16">
                      <path d="m12.14 8.753-5.482 4.796c-.646.566-1.658.106-1.658-.753V3.204a1 1 0 0 1 1.659-.753l5.48 4.796a1 1 0 0 1 0 1.506z" />
                    </svg>
                  </button>
                </div>
              </div>
            </div>
          </form>
        </div>
      </Container >
    </>
  );
}

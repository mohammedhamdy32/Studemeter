import Head from "next/head";
import Container from "react-bootstrap/Container";
import Header from "@/components/Header";
import Link from "next/link";
import { useRouter } from "next/router";
import ScatterPlot from "./scatterplot";


function handleViewHistoryClick(studentId: number) {
  console.log(studentId)
}

interface StudentParams {
  id: number,
  name: string, 
  isDistracted: boolean,
}

function StudentDiv({id, name, isDistracted}: StudentParams) {
  return (
    <div className="row mx-1 my-2">
      <div className="col-12">
        <div className={"row justify-content-between p-2 rounded-4 bg-opacity-10 " + (isDistracted ? "bg-secondary" : "bg-primary")}>
          <div className="col-12 fs-4">
            {name}
          </div>
          <div className="col-auto fs-6 text-uppercase fg-primary">
            {isDistracted ?              
              <span className="text-secondary font-weight-bold">Distracted</span>
            : <span className="text-primary">normal</span>}
          </div>
          <Link href="/history" className="btn btn-sm col-auto rounded-pill fs-6 text-uppercase opacity-50">
            view history
            <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" className="bi bi-caret-right-fill" viewBox="0 0 16 16">
              <path d="m12.14 8.753-5.482 4.796c-.646.566-1.658.106-1.658-.753V3.204a1 1 0 0 1 1.659-.753l5.48 4.796a1 1 0 0 1 0 1.506z" />
            </svg>
          </Link>
        </div>
      </div>
    </div>
  );
}

export default function Home() {
  const studentName = "Amir Abdullah";
  const startDatetime = "8:00 AM";
  const endDatetime = "now";

  const router = useRouter();
  const handleButtonClick = () => {
    router.push('/students');
  }

  return (
    <>
      <Head>
        <title>Studemeter</title>
        <meta name="description" content="Students Focus Monitoring System" />
        <meta name="viewport" content="width=device-width, initial-scale=1" />
        <link rel="icon" href="/favicon.ico" />
      </Head>
      <Container as="main" className="py-4 px-3 mx-auto">
        <Header text="" href="/" />

        <div className="row justify-content-center">

          <div className="col-12 col-lg-6 justify-content-center p-0 border rounded-4">

            <div className="bg-light rounded-4">
              <div className="row justify-content-center">
                <div className="col-12 fs-4 text-center my-2">
                  {studentName}
                </div>
                <div className="div-12 mb-2">
                  <div className="row text-center">
                    <div className="col-12">
                        <div>
                            <span className="text-primary text-capitalize"> mostly focused </span> from {startDatetime} till {endDatetime}
                        </div>
                        <div className="text-secondary text-capitalize">
                            currently distracted
                        </div>
                    </div>
                  </div>
                </div>
              </div>
            </div>

            <div className="col my-1">
                <ScatterPlot />
            </div>

            <div className="bg-light rounded-4">
              <div className="row justify-content-center">
                <div className="div-12 mb-2">



                <div className="text-uppercase text-center mt-2 mb-2 fs-6 opacity-50">
            time period to display in
           </div>

           <div className="">
              <div className="row justify-content-center py-2 px-5">
                <div className="form-check col-6 col-md-5 col-lg-4">
                    <input className="form-check-input" type="radio" name="flexRadioDefault" id="opt1" checked />
                    <label className="form-check-label text-capitalize" htmlFor="opt1">
                        during class
                    </label>
                </div>
                <div className="form-check col-6 col-md-5 col-lg-4">
                    <input className="form-check-input" type="radio" name="flexRadioDefault" id="opt2" />
                    <label className="form-check-label text-capitalize" htmlFor="opt2">
                        today
                    </label>
                </div>
                <div className="w-100"></div>
                <div className="form-check col-6 col-md-5 col-lg-4">
                    <input className="form-check-input" type="radio" name="flexRadioDefault" id="opt3" />
                    <label className="form-check-label text-capitalize" htmlFor="opt3">
                        this week
                    </label>
                </div>
                <div className="form-check col-6 col-md-5 col-lg-4">
                    <input className="form-check-input" type="radio" name="flexRadioDefault" id="opt4" />
                    <label className="form-check-label text-capitalize" htmlFor="opt4">
                        this month
                    </label>
                </div>
              </div>
            </div>
          
                </div>
              </div>
            </div>



           </div>

        
            <div className="col-12 mt-4">
              <div className="row justify-content-center">
                <div className="col-auto">
                  <button type="button" onClick={handleButtonClick} className="text-capitalize btn btn-primary rounded-pill">
                    <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" className="bi bi-caret-left-fill" viewBox="0 0 16 16">
                        <path d="m3.86 8.753 5.482 4.796c.646.566 1.658.106 1.658-.753V3.204a1 1 0 0 0-1.659-.753l-5.48 4.796a1 1 0 0 0 0 1.506z" />
                    </svg>
                    back
                  </button>
                </div>
              </div>
            </div>


         </div>
       </Container >
     </>
   );
 }
 
 
 
 
 
 
